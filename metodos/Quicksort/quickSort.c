#include "quickSort.h"
#include "area.h"

void quickSort(Dados *Dados)
{

    FILE *ArqLi = fopen(Dados->nomeArquivo, "rb+");
    if (ArqLi == NULL)
    {
        perror("Error opening file for reading");
        exit(EXIT_FAILURE);
    }
    FILE *ArqEi = fopen(Dados->nomeArquivo, "rb+");
    if (ArqEi == NULL)
    {
        perror("Error opening file for reading");
        fclose(ArqLi);
        exit(EXIT_FAILURE);
    }
    FILE *ArqLEs = fopen(Dados->nomeArquivo, "rb+");
    if (ArqLEs == NULL)
    {
        perror("Error opening file for reading");
        fclose(ArqLi);
        fclose(ArqEi);
        exit(EXIT_FAILURE);
    }

    TipoArea Area;
    inicializaArea(&Area);
    QuicksortExterno(&ArqLi, &ArqEi, &ArqLEs, 1, Dados->quantidade, Dados);

    fclose(ArqLi);
    fclose(ArqEi);
    fclose(ArqLEs);
}

void QuicksortExterno(FILE **ArqLi, FILE **ArqEi, FILE **ArqLEs, int Esq, int Dir, Dados *Dados)
{
    int i, j;

    if (Dir - Esq < 1)
        return;

    TipoArea Area = inicializaArea();

    Particao(ArqLi, ArqEi, ArqLEs, Area, Esq, Dir, &i, &j, Dados);

    fflush(*ArqLi);
    fflush(*ArqEi);
    fflush(*ArqLEs);

    if (i - Esq < Dir - j)
    {
        QuicksortExterno(ArqLi, ArqEi, ArqLEs, Esq, i, Dados);
        QuicksortExterno(ArqLi, ArqEi, ArqLEs, j, Dir, Dados);
    }
    else
    {
        QuicksortExterno(ArqLi, ArqEi, ArqLEs, j, Dir, Dados);
        QuicksortExterno(ArqLi, ArqEi, ArqLEs, Esq, i, Dados);
    }
}

// Le o dado do arquivo superior
void LeSup(FILE **ArqLEs, TipoRegistro *UltLido, int *Ls, short *OndeLer, Dados *Dados)
{
    fseek(*ArqLEs, (*Ls - 1) * sizeof(TipoRegistro), SEEK_SET);
    fread(UltLido, sizeof(TipoRegistro), 1, *ArqLEs);

    Dados->acessos.num_leituras++;

    (*Ls)--;
    *OndeLer = false;
}

// Le o dado do arquivo inferior
void LeInf(FILE **ArqLi, TipoRegistro *UltLido, int *Li, short *OndeLer, Dados *Dados)
{
    fread(UltLido, sizeof(TipoRegistro), 1, *ArqLi);

    Dados->acessos.num_leituras++;

    (*Li)++;
    *OndeLer = true;
}

void InserirArea(TipoArea *Area, TipoRegistro *UltLido, int *NRArea, Dados *Dados)
{
    // Insere UltLido de forma ordenada na Area
    InsereItem(*UltLido, Area, Dados);
    *NRArea = ObterNumCelOcupadas(Area);
}

// Escreve o item no arquivo superior
void EscreveMax(FILE **ArqLEs, TipoRegistro R, int *Es, Dados *Dados)
{
    fseek(*ArqLEs, (*Es - 1) * sizeof(TipoRegistro), SEEK_SET);
    fwrite(&R, sizeof(TipoRegistro), 1, *ArqLEs);

    Dados->acessos.num_escritas++;

    (*Es)--;
}

// Escreve o item no arquivo inferior
void EscreveMin(FILE **ArqEi, TipoRegistro R, int *Ei, Dados *Dados)
{

    Dados->acessos.num_escritas++;

    fwrite(&R, sizeof(TipoRegistro), 1, *ArqEi);
    (*Ei)++;
}

// Remove o maior valor do pivo
void RetiraMax(TipoArea *Area, TipoRegistro *R, int *NRArea)
{
    RetiraUltimo(Area, R);
    *NRArea = ObterNumCelOcupadas(Area);
}

// Remove o menor valor do pivo
void RetiraMin(TipoArea *Area, TipoRegistro *R, int *NRArea)
{
    RetiraPrimeiro(Area, R);
    *NRArea = ObterNumCelOcupadas(Area);
}

void Particao(FILE **ArqLi, FILE **ArqEi, FILE **ArqLEs, TipoArea Area, int Esq, int Dir, int *i, int *j, Dados *Dados)
{
    int Ls = Dir, Es = Dir, Li = Esq, Ei = Esq, NRArea = 0;
    double Linf = INT_MIN, Lsup = INT_MAX;
    short OndeLer = true;
    TipoRegistro UltLido, R;

    fseek(*ArqLi, (Li - 1) * sizeof(TipoRegistro), SEEK_SET);
    fseek(*ArqEi, (Ei - 1) * sizeof(TipoRegistro), SEEK_SET);

    *i = Esq - 1;
    *j = Dir + 1;

    // Lendo ate que os ponteiros de leitura se cruzem
    while (Ls >= Li)
    {
        if (NRArea < TAMAREA - 1)
        {
            if (OndeLer)
                LeSup(ArqLEs, &UltLido, &Ls, &OndeLer, Dados);
            else
                LeInf(ArqLi, &UltLido, &Li, &OndeLer, Dados);

            InserirArea(&Area, &UltLido, &NRArea, Dados);
            continue;
        }

        // Lendo na alternancia correta
        // Verifica se os ponteiros de leitura e escrita estao juntos para mudar a alternancia da leitura
        if (Ls == Es)
            LeSup(ArqLEs, &UltLido, &Ls, &OndeLer, Dados);
        else if (Li == Ei)
            LeInf(ArqLi, &UltLido, &Li, &OndeLer, Dados);
        else if (OndeLer)
            LeSup(ArqLEs, &UltLido, &Ls, &OndeLer, Dados);
        else
            LeInf(ArqLi, &UltLido, &Li, &OndeLer, Dados);

        // Tratativa do ultimo item lido
        // Caso em que o ultimo elemento vai para o subarquivo A2 (itens superiores ao pivo)
        if (UltLido.nota > Lsup)
        {
            *j = Es;
            EscreveMax(ArqLEs, UltLido, &Es, Dados);
            continue;
        }

        Dados->acessos.num_comparacoes++;

        // Caso em que o ultimo elemento vai para o subarquivo A1 (itens inferiores ao pivo)
        if (UltLido.nota < Linf)
        {
            *i = Ei;
            EscreveMin(ArqEi, UltLido, &Ei, Dados);
            continue;
        }

        Dados->acessos.num_comparacoes++;

        // Caso em que o ultimo elemento vai para o pivo
        InserirArea(&Area, &UltLido, &NRArea, Dados);

        // Verificando qual o menor sub arquivo e escrevendo nele
        if (Ei - Esq < Dir - Es)
        {
            RetiraMin(&Area, &R, &NRArea);
            EscreveMin(ArqEi, R, &Ei, Dados);
            Linf = R.nota;
        }
        else
        {
            RetiraMax(&Area, &R, &NRArea);
            EscreveMax(ArqLEs, R, &Es, Dados);
            Lsup = R.nota;
        }
    }

    while (Ei <= Es)
    {
        RetiraMin(&Area, &R, &NRArea);
        EscreveMin(ArqEi, R, &Ei, Dados);
    }
}

// funcao para comparacao de dois registros, levando em conta sua marcacao e sua nota

int compare(const RegistroSubstituicao registro1, const RegistroSubstituicao registro2, Dados *Dados)
{
    // retornos: 1 = registro1 > registro2, 0 = registro1 <= registro2

    if (registro1.substituir == registro2.substituir)
    {
        Dados->acessos.num_comparacoes++;

        if (registro1.registro.nota > registro2.registro.nota)
            return 1;
        else
            return 0;
    }
    else if (registro1.substituir && !registro2.substituir)
        return 1;

    // caso em que o primeiro nao e marcado, e o segundo e marcado
    return 0;
}

// QuickSort Interno:

void trocarPosicao(TipoRegistro *registro, int *i, int *j)
{
    TipoRegistro auxiliar;

    auxiliar = registro[*i];
    registro[*i] = registro[*j];
    registro[*j] = auxiliar;
    *i += 1;
    *j -= 1;
}

void trocarPosicao2(RegistroSubstituicao *registros, int *i, int *j)
{
    RegistroSubstituicao auxiliar;

    auxiliar = registros[*i];
    registros[*i] = registros[*j];
    registros[*j] = auxiliar;
    *i += 1;
    *j -= 1;
}

// quickSort utilizado na geracao de blocos por ordenacao
void quicksortInterno(TipoRegistro *registro, int inicio, int fim, Dados *Dados)
{
    int i, j;
    TipoRegistro pivo;

    i = inicio;
    j = fim;
    pivo = registro[(inicio + fim) / 2];

    while (i <= j)
    {
        Dados->acessos.num_comparacoes++;
        while (registro[i].nota < pivo.nota && i < fim)
        {
            i++;
            Dados->acessos.num_comparacoes++;
        }

        Dados->acessos.num_comparacoes++;
        
        while (registro[j].nota > pivo.nota && j > inicio)
        {
            j--;
            Dados->acessos.num_comparacoes++;
        }
        if (i <= j)
            trocarPosicao(registro, &i, &j);
    }

    if (j > inicio)
        quicksortInterno(registro, inicio, j, Dados);

    if (i < fim)
        quicksortInterno(registro, i, fim, Dados);
}

// quickSort utilizado na geracao de blocos utilizando selecao por substituicao
void quicksortInterno_SelecaoSubstituicao(RegistroSubstituicao *registros, int inicio, int fim, Dados *Dados)
{
    int i, j;
    RegistroSubstituicao pivo;

    i = inicio;
    j = fim;
    pivo = registros[(inicio + fim) / 2];

    while (i <= j)
    {
        // enquanto registros[i] < pivo
        while (compare(pivo, registros[i], Dados) && i < fim)
            i++;

        // enquanto registros[j] > pivo
        while (compare(registros[j], pivo, Dados) && j > inicio)
            j--;

        if (i <= j)
            trocarPosicao2(registros, &i, &j);
    }

    if (j > inicio)
        quicksortInterno_SelecaoSubstituicao(registros, inicio, j, Dados);

    if (i < fim)
        quicksortInterno_SelecaoSubstituicao(registros, i, fim, Dados);
}