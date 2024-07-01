#ifndef GRAFO_H
#define GRAFO_H

typedef struct Adjacente {
    int destino;
    int peso;
    struct Adjacente* proximo;
} Adjacente;

typedef struct Vertice {
    Adjacente* listaAdj;
    int peso;
    int visitado;
} Vertice;

void dijkstra(Vertice vertices[], int tamanho, int origem, int destino, int anteriorOrdenado[], int op);

int encontrarMenorDistancia(Vertice vertices[], int tamanho);

void caminhoMinimo(int anterior[], int anteriorOrdenado[], int tamanho, int destino);

void imprimirCaminhoMinimo(int anteriorOrdenado[], int tamanho);

void interacaoComUsuario(int anteriorOrdenado[], int tamanho, int destino);

void liberarListaAdjacencia(Vertice vertices[], int tamanho, int anteriorOrdenado[]);

void lerGrafo(FILE* fp, Vertice vertices[], int tamanho, int* origem, int* destino, int op);

void adicionarAresta(Vertice* vertices, int origem, int destino, int peso);

Adjacente* criarAdjacente(int destino, int peso);

void imprimeGrafo(Vertice* vertices, int tamanho);

void opcao1(int op, char nomeArquivo[]);

void opcao2(int op);

void opcao3(int op);

#endif