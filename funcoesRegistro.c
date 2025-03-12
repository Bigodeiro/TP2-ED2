#include "funcoesRegistro.h"

// Função para ler um registro do arquivo
bool lerRegistro(FILE *arquivo, TipoRegistro *reg, AcessoArquivo *acessos)
{
    char linha[MAX_REG_LINHA];

    if (fgets(linha, MAX_REG_LINHA, arquivo) == NULL)
    {
        return false;
    }

    acessos->num_leituras++;

    // Extrai os campos da linha conforme as posições especificadas
    char inscricao_str[9] = {0};
    char nota_str[6] = {0};
    char estado[3] = {0};
    char cidade[51] = {0};
    char curso[31] = {0};

    strncpy(inscricao_str, linha, 8);
    strncpy(nota_str, linha + 9, 5);
    strncpy(estado, linha + 15, 2);
    strncpy(cidade, linha + 18, 50);
    strncpy(curso, linha + 69, 30);

    reg->inscricao = atol(inscricao_str);
    reg->nota = atof(nota_str);
    strcpy(reg->estado, estado);
    strcpy(reg->cidade, cidade);
    strcpy(reg->curso, curso);

    return true;
}

// Função para escrever um registro no arquivo
void escreverRegistro(FILE *arquivo, TipoRegistro *reg, AcessoArquivo *acessos)
{
    fprintf(arquivo, "%8ld %5.1f %2s %50s %30s\n", reg->inscricao, reg->nota,
            reg->estado, reg->cidade, reg->curso);

    acessos->num_escritas++;
}

// Função para imprimir um registro na tela
void imprimirRegistro(TipoRegistro *reg) {
    printf("%8ld %5.1f %2s %50s %30s\n", reg->inscricao, reg->nota, reg->estado,
           reg->cidade, reg->curso);
}

// Função para comparar dois registros (pela nota)
int compararRegistros(TipoRegistro *a, TipoRegistro *b, AcessoArquivo *acessos) {
    acessos->num_comparacoes++;
    
    if (a->nota < b->nota) return -1;
    if (a->nota > b->nota) return 1;
    return 0;
}



