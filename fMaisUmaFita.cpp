#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <limits>
using namespace std;

#define TAMANHO_MEMORIA 19

typedef struct TipoRegistro {
    long int numeroInscr;
    float nota;
    char estado[2];
    char cidade[50];
    char curso[30];
};

/* ---- LEITURA DO ARQUIVO E REGISTROS ---- */
bool abrirArquivo(FILE *arq, string nomeDoArquivo) {
    arq = fopen(nomeDoArquivo.c_str(), "w+r");
    if (arq == nullptr) {
        printf("Arquivo nao pode ser aberto\n");
        return false;
    }
    return true;
}

bool preencheMemoriaInterna(FILE *arq, TipoRegistro *memoriaInterna) {
    for(int i = 0; i < TAMANHO_MEMORIA; i++) {
        if(!fread(&(memoriaInterna[i]), sizeof(TipoRegistro), 1, arq))
            return false;
    }
    return true;
}

/* ---- PREENCHIMENTO DAS FITAS DE ENTRADA ---- */

void trocar(TipoRegistro *a, TipoRegistro *b) {
    TipoRegistro temp = *a;
    *a = *b;
    *b = temp;
}

bool compararRegistros(TipoRegistro a, TipoRegistro b) {
    if (a.marcado != b.marcado) {
        return a.marcado > b.marcado;  // Registros marcados devem ser maiores
    }
    return a.nota < b.nota;  // Caso contrário, ordena por nota
}

void heapify(TipoRegistro heap[], int n, int i) {
    int menor = i;
    int esq = 2 * i + 1;
    int dir = 2 * i + 2;

    if (esq < n && compararRegistros(heap[esq], heap[menor]))
        menor = esq;

    if (dir < n && compararRegistros(heap[dir], heap[menor]))
        menor = dir;

    if (menor != i) {
        trocar(&heap[i], &heap[menor]);
        heapify(heap, n, menor);
    }
}

void constroiHeap(TipoRegistro heap[], int tamanho) {
    for (int i = tamanho / 2 - 1; i >= 0; i--)
        heapify(heap, tamanho, i);
}

void geraSubSelecao(FILE *arqEntrada, TipoRegistro *memoriaInterna, int numeroDeRegistrosASerLido, FILE *fitas[3],
                            int fitaAtual = 0, int &numeroDeFitasUsadas) {

    int contadorDeRegistrosEscritos = 0;
    int ultimaNotaEscrita;
    
    preencheMemoriaInterna(arqEntrada, memoriaInterna);
    constroiHeap(memoriaInterna, TAMANHO_MEMORIA);

    while (contadorDeRegistrosEscritos < numeroDeRegistrosASerLido) {

        TipoRegistro menorRegistro = memoriaInterna[0];
        fwrite(&menorRegistro, sizeof(TipoRegistro), 1, fitas[fitaAtual]);
        contadorDeRegistrosEscritos++;
        ultimaNotaEscrita = menorRegistro.nota;

        TipoRegistro novoRegistro;
        if (fread(&novoRegistro, sizeof(TipoRegistro), 1, arqEntrada)) {
            if (novoRegistro.nota < ultimaNotaEscrita) {
                memoriaInterna[0].nota += 100;
            }
            memoriaInterna[0] = novoRegistro;
        }

        heapify(memoriaInterna, TAMANHO_MEMORIA, 0);

        bool todosMarcados = true;
        for (int i = 0; i < TAMANHO_MEMORIA; i++) 
            if (memoriaInterna[i].nota < 100) {
                todosMarcados = false;
                break;
            }
        

        if(todosMarcados) {
            numeroDeFitasUsadas++;
            fitaAtual = (fitaAtual + 1) % TAMANHO_MEMORIA;
            ultimaNotaEscrita = 0;
            for(int i = 0; i < TAMANHO_MEMORIA; i++) 
                if(fread(&memoriaInterna[i], sizeof(TipoRegistro), 1, arqEntrada)) {
                    memoriaInterna[i].nota -= 100;
                }
            
                constroiHeap(memoriaInterna, TAMANHO_MEMORIA);
        }
    }
}

/* ---- PREENCHIMENTO DA FITA DE SAIDA ---- */

void intercalarRegistros(FILE *fitasEntrada[], FILE *fitaSaida, int numFitasUsadas) {
    HeapNode heap[TAMANHO_MEMORIA]; // Heap com 19 espaços
    int registrosRestantes = 0; // Contador de registros restantes nas fitas

    // Inicializa o heap com o primeiro registro de cada fita usada
    for (int i = 0; i < numFitasUsadas; i++) {
        if (fread(&heap[i], sizeof(TipoRegistro), 1, fitasEntrada[i])) {
            heap[i].fitaOrigem = i; // Armazena a fita de origem do registro
            registrosRestantes++;
        } else {
            heap[i].nota = numeric_limits<float>::max(); // Marca como infinito se a fita estiver vazia
        }
    }

    // Constrói o heap inicial
    constroiHeap(heap, numFitasUsadas);

    // Intercala os registros enquanto houver registros restantes
    while (registrosRestantes > 0) {
        // O menor registro está na raiz do heap (heap[0])
        TipoRegistro menorRegistro = heap[0];
        int fitaOrigem = heap[0].fitaOrigem;

        // Escreve o menor registro na fita de saída
        fwrite(&menorRegistro, sizeof(TipoRegistro), 1, fitaSaida);

        // Lê o próximo registro da fita de origem
        if (fread(&heap[0], sizeof(TipoRegistro), 1, fitasEntrada[fitaOrigem]) != 1) {
            // Se a fita estiver vazia, marca o registro como infinito
            heap[0].nota = numeric_limits<float>::max();
            registrosRestantes--;
        }

        // Reajusta o heap após a substituição
        heapify(heap, numFitasUsadas, 0);
    }
}

void redistribuirBlocos(FILE *fitaSaida, FILE *fitasEntrada[], int numFitasUsadas) {
    TipoRegistro bloco[TAMANHO_MEMORIA]; // Bloco de registros
    int fitaAtual = 0; // Índice da fita de entrada atual

    // Lê os blocos da fita de saída e redistribui para as fitas de entrada
    while (true) {
        // Lê um bloco de registros da fita de saída
        size_t registrosLidos = fread(bloco, sizeof(TipoRegistro), TAMANHO_MEMORIA, fitaSaida);

        // Se não houver mais registros, encerra o loop
        if (registrosLidos == 0) {
            break;
        }

        // Escreve o bloco na fita de entrada atual
        fwrite(bloco, sizeof(TipoRegistro), registrosLidos, fitasEntrada[fitaAtual]);

        // Alterna para a próxima fita de entrada
        fitaAtual = (fitaAtual + 1) % numFitasUsadas;
    }

    // Fecha a fita de saída
    fclose(fitaSaida);
}

void ordenacaoExterna(FILE *arqEntrada, FILE *fitaSaida, TipoRegistro memoriaInterna[], FILE *fitas[], int numeroDeRegistros) {

    int contadorDeRegistrosLidos = 0;
    int numeroDeFitasUsadas = 1;
    geraSubSelecao(arqEntrada, memoriaInterna, numeroDeRegistros, fitas, numeroDeFitasUsadas);
    if(numeroDeFitasUsadas > 19)
        numeroDeFitasUsadas = 19;
    intercalarRegistros(fitas, fitaSaida, numeroDeFitasUsadas);

}

int main() {

    char nomeArquivo[10];
    FILE *fitas[TAMANHO_MEMORIA];
    FILE *fitaSaida = fopen("f20.txt", "w");
    FILE *arqEntrada = nullptr;

    // [*arq][*arq1][][][][]

    /* abrindo fitas de entrada */
    for(int i = 0; i < TAMANHO_MEMORIA; i++) {
        sprintf(nomeArquivo, "f%d.txt", i + 1); // Gera o nome do arquivo (f1.txt, f2.txt, ..., f19.txt)
        if(!abrirArquivo(fitas[i], nomeArquivo)) return 1;
    }

    if(!(arqEntrada = fopen("PROVAO.TXT", "r"))) return 1;

    TipoRegistro memoriaInterna[TAMANHO_MEMORIA];
    int numeroDeRegistros;
    ordenacaoExterna(arqEntrada, fitaSaida, memoriaInterna, fitas, numeroDeRegistros);
    
    for(int i = 0; i < TAMANHO_MEMORIA; i++) {
        fclose(fitas[i]);
    }
    fclose(fitaSaida)

}
