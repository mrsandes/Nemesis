#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "Grafo.h"

#define VALOR_MAX 2147483647
#define TRUE 1
#define FALSE 0

void dijkstra(Vertice vertices[], int tamanho, int origem, int destino, int anteriorOrdenado[], int op) {
    int anterior[tamanho], u, v;
    Adjacente *adjacente;

    vertices[origem].peso = 0;

    for (int i = 0; i < tamanho; i++) {
        anterior[i] = -1;
        anteriorOrdenado[i] = -1;
    }

    for (int i = 0; i < tamanho - 1; i++) {
        u = encontrarMenorDistancia(vertices, tamanho);

        if (u == -1) {
            break;
        }

        vertices[u].visitado = TRUE;
        adjacente = vertices[u].listaAdj;

        while (adjacente != NULL) {
            v = adjacente->destino;

            if (!vertices[v].visitado && vertices[u].peso != VALOR_MAX && vertices[u].peso + adjacente->peso < vertices[v].peso) {
                vertices[v].peso = vertices[u].peso + adjacente->peso;
                anterior[v] = u;
            }

            adjacente = adjacente->proximo;
        }
    }

    caminhoMinimo(anterior, anteriorOrdenado, tamanho, destino);

    if (op != 2) {
        printf("\tCaminho mais rapido de %d ate %d: ", origem, destino);

        imprimirCaminhoMinimo(anteriorOrdenado, tamanho);
        
        printf("\n\tPeso total do percurso: %d\n", vertices[destino].peso);
    }
}

int encontrarMenorDistancia(Vertice vertices[], int tamanho) {
    int minimo = VALOR_MAX;
    int indiceMinimo = -1;

    for (int i = 0; i < tamanho; i++) {
        if (!vertices[i].visitado && vertices[i].peso < minimo) {
            minimo = vertices[i].peso;
            indiceMinimo = i;
        }
    }

    return indiceMinimo;
}

void caminhoMinimo(int anterior[], int anteriorOrdenado[], int tamanho, int destino) {
    int posicao = destino;

    anteriorOrdenado[0] = destino;
    for (int i = 1; i < tamanho; i++) {
        anteriorOrdenado[i] = anterior[posicao];
        posicao = anterior[posicao]; 

        if (posicao == 0) {
            break;
        }
    }
}

void imprimirCaminhoMinimo(int anteriorOrdenado[], int tamanho) {
    for (int i = tamanho - 1; i >= 0; i--) {
        if (anteriorOrdenado[i] != -1) {
            printf("%d ", anteriorOrdenado[i]);
        }
    }
}

void interacaoComUsuario(int anteriorOrdenado[], int tamanho, int destino) {
    int* caminho = (int*)malloc(sizeof(int) * tamanho);
    int* caminhoOrdenado = (int*)malloc(sizeof(int) * tamanho);

    int j = 0;
    char c;

    for (int i = 0; i < tamanho; i++) {
        caminho[i] = -1;
        caminhoOrdenado[i] = -1;
    }

    printf("\tDigite o caminho mais rapido encontrado por voce: ");

    for (int i = 0; i < tamanho; i++) {
        scanf("%d%c", &caminho[i], &c);

        if (c == '\n') {
            break;
        }
    }

    for (int i = tamanho - 1; i >= 0; i--) {
        if (caminho[i] != -1) {
            caminhoOrdenado[j] = caminho[i];
            j++;
        }
    }

    for (int i = 0; i < tamanho; i++) {
        if (caminhoOrdenado[i] != anteriorOrdenado[i]) {
            printf("\n\tQue pena! Voce nao achou o caminho mais rapido de Hercules ate Euterpe\n\tO caminho mais rapido era: ");
            imprimirCaminhoMinimo(anteriorOrdenado, tamanho);
            printf("\n");
            break;
        }

        if (i == tamanho - 1) {
            printf("\n\tParabens! Voce acertou o caminho mais rapido ate Euterpe!\n");
        }
    }
    
    free(caminho);
    free(caminhoOrdenado);
}

void liberarListaAdjacencia(Vertice vertices[], int tamanho, int anteriorOrdenado[]) {
    Adjacente *proximo;
    Adjacente *atual;

    for (int i = 0; i < tamanho; i++) {
        atual = vertices[i].listaAdj;

        while (atual != NULL) {
            proximo = atual->proximo;
            free(atual);
            atual = proximo;
        }
    }

    
    free(vertices);
    free(anteriorOrdenado);
}

void lerGrafo(FILE *fp, Vertice vertices[], int tamanho, int *origem, int *destino, int op) {
    int orig, dest, peso;

    fscanf(fp, "%d %d", origem, destino);

    for (int i = 0; i < tamanho; i++) {
        vertices[i].listaAdj = NULL;
        vertices[i].peso = VALOR_MAX;
        vertices[i].visitado = FALSE;
    }

    srand(time(NULL));

    if (op == 2) {
        *destino = (rand() % 65) + 1;
    }

    while (fscanf(fp, "%d %d %d", &orig, &dest, &peso) == 3) {
        if (op == 2) {
            peso = (rand() % 99) + 1;
        }

        adicionarAresta(vertices, orig, dest, peso);
        adicionarAresta(vertices, dest, orig, peso);
    }

    fclose(fp);
}

void adicionarAresta(Vertice *vertices, int origem, int destino, int peso) {
    Adjacente *novo = criarAdjacente(destino, peso);

    novo->proximo = vertices[origem].listaAdj;
    vertices[origem].listaAdj = novo;
}

Adjacente *criarAdjacente(int destino, int peso) {
    Adjacente *novo = (Adjacente*)malloc(sizeof(Adjacente));

    novo->destino = destino;
    novo->peso = peso;
    novo->proximo = NULL;

    return novo;
}

void imprimeGrafo(Vertice* vertices, int tamanho) {
    printf("\n\tGrafo:\n");

    for (int i = 0; i < tamanho; i++) {
        printf("\t%d: ", i);

        Adjacente* atual = vertices[i].listaAdj;
        while (atual != NULL) {
            printf("%d(%d) ", atual->destino, atual->peso);
            atual = atual->proximo;
        }

        printf("\n");
    }

    printf("\n");
}

void opcao1(int op, char nomeArquivo[]) {
    Vertice *vertices;
    int tamanho, origem, destino;
    int* anteriorOrdenado;

    FILE* fp = fopen(nomeArquivo, "r");

    if (fp == NULL) {
        printf("\tErro ao abrir o arquivo\n");
        exit(1);
    }

    fscanf(fp, "%d", &tamanho);

    anteriorOrdenado = (int*)malloc(sizeof(int) * tamanho);
    vertices = (Vertice*)malloc(sizeof(Vertice) * tamanho);

    lerGrafo(fp, vertices, tamanho, &origem, &destino, op);

    imprimeGrafo(vertices, tamanho);

    printf("\n");
    dijkstra(vertices, tamanho, origem, destino, anteriorOrdenado, op);
    
    liberarListaAdjacencia(vertices, tamanho, anteriorOrdenado);
}

void opcao2(int op) {
    Vertice *vertices;
    int tamanho, origem, destino;
    int* anteriorOrdenado;

    FILE* fp = fopen("Opcao2.txt", "r");

    if (fp == NULL) {
        printf("\tErro ao abrir o arquivo\n");
        exit(1);
    }

    fscanf(fp, "%d", &tamanho);

    anteriorOrdenado = (int*)malloc(sizeof(int) * tamanho);
    vertices = (Vertice*)malloc(sizeof(Vertice) * tamanho);

    lerGrafo(fp, vertices, tamanho, &origem, &destino, op);

    dijkstra(vertices, tamanho, origem, destino, anteriorOrdenado, op);

    printf(
    "\t                                                                                                                                                          \n"
    "\t                                  |09| -%02d - |16| -%02d - |23| -%02d - |30| -%02d - |37| -%02d - |44| -%02d - |51|                                       \n"
    "\t                                   |          |          |          |          |          |          |                                                      \n"
    "\t                                   %02d         %02d         %02d         %02d         %02d         %02d         %02d                                        \n"
    "\t                                   |          |          |          |          |          |          |                                                        \n"
    "\t                       |04| -%02d - |10| -%02d - |17| -%02d - |24| -%02d - |31| -%02d - |38| -%02d - |45| -%02d - |52| -%02d - |58|                            \n"
    "\t                        |          |          |          |          |          |          |          |          |                                               \n"
    "\t                        %02d         %02d         %02d         %02d         %02d         %02d         %02d         %02d         %02d                             \n"
    "\t                        |          |          |          |          |          |          |          |          |                                                 \n"
    "\t            |01| -%02d - |05| -%02d - |11| -%02d - |18| -%02d - |25| -%02d - |32| -%02d - |39| -%02d - |46| -%02d - |53| -%02d - |59| -%02d - |63|                 \n"
    "\t             |          |          |          |          |          |          |          |          |          |          |                                        \n"
    "\t             %02d         %02d         %02d         %02d         %02d         %02d         %02d         %02d         %02d         %02d         %02d                  \n"
    "\t             |          |          |          |          |          |          |          |          |          |          |                                          \n"
    "\t |00| -%02d - |02| -%02d - |06| -%02d - |12| -%02d - |19| -%02d - |26| -%02d - |33| -%02d - |40| -%02d - |47| -%02d - |54| -%02d - |60| -%02d - |64|                   \n"
    "\t             |          |          |          |          |          |          |          |          |          |          |                                          \n"
    "\t             %02d         %02d         %02d         %02d         %02d         %02d         %02d         %02d         %02d         %02d         %02d                  \n"
    "\t             |          |          |          |          |          |          |          |          |          |          |                                        \n"
    "\t            |03| -%02d - |07| -%02d - |13| -%02d - |20| -%02d - |27| -%02d - |34| -%02d - |41| -%02d - |48| -%02d - |55| -%02d - |61| -%02d - |65|                 \n"
    "\t                        |          |          |          |          |          |          |          |          |                                                 \n"
    "\t                        %02d         %02d         %02d         %02d         %02d         %02d         %02d         %02d         %02d                             \n"
    "\t                        |          |          |          |          |          |          |          |          |                                               \n"
    "\t                       |08| -%02d - |14| -%02d - |21| -%02d - |28| -%02d - |35| -%02d - |42| -%02d - |49| -%02d - |56| -%02d - |62|                            \n"
    "\t                                   |          |          |          |          |          |          |                                                        \n"
    "\t                                   %02d         %02d         %02d         %02d         %02d         %02d         %02d                                        \n"
    "\t                                   |          |          |          |          |          |          |                                                      \n"
    "\t                                  |15| -%02d - |22| -%02d - |29| -%02d - |36| -%02d - |43| -%02d - |50| -%02d - |57|                                       \n"
    "\t                                                                                                                                                          \n", 
    vertices[9].listaAdj->proximo->peso, vertices[16].listaAdj->proximo->peso, vertices[23].listaAdj->proximo->peso, vertices[30].listaAdj->proximo->peso, vertices[37].listaAdj->proximo->peso, vertices[44].listaAdj->proximo->peso,
    vertices[9].listaAdj->peso, vertices[16].listaAdj->peso, vertices[23].listaAdj->peso, vertices[30].listaAdj->peso, vertices[37].listaAdj->peso, vertices[44].listaAdj->peso, vertices[51].listaAdj->peso,
    vertices[4].listaAdj->proximo->peso, vertices[10].listaAdj->proximo->peso, vertices[17].listaAdj->proximo->peso, vertices[24].listaAdj->proximo->peso, vertices[31].listaAdj->proximo->peso, vertices[38].listaAdj->proximo->peso, vertices[45].listaAdj->proximo->peso, vertices[52].listaAdj->proximo->peso,
    vertices[4].listaAdj->peso, vertices[10].listaAdj->peso, vertices[17].listaAdj->peso, vertices[24].listaAdj->peso, vertices[31].listaAdj->peso, vertices[38].listaAdj->peso, vertices[45].listaAdj->peso, vertices[52].listaAdj->peso, vertices[58].listaAdj->peso,
    vertices[1].listaAdj->proximo->peso, vertices[5].listaAdj->proximo->peso, vertices[11].listaAdj->proximo->peso, vertices[18].listaAdj->proximo->peso, vertices[25].listaAdj->proximo->peso, vertices[32].listaAdj->proximo->peso, vertices[39].listaAdj->proximo->peso, vertices[46].listaAdj->proximo->peso, vertices[53].listaAdj->proximo->peso, vertices[59].listaAdj->proximo->peso, 
    vertices[1].listaAdj->peso, vertices[5].listaAdj->peso, vertices[11].listaAdj->peso, vertices[18].listaAdj->peso, vertices[25].listaAdj->peso, vertices[32].listaAdj->peso, vertices[39].listaAdj->peso, vertices[46].listaAdj->peso, vertices[53].listaAdj->peso, vertices[59].listaAdj->peso, vertices[63].listaAdj->peso, 
    vertices[0].listaAdj->peso, vertices[2].listaAdj->proximo->peso, vertices[6].listaAdj->proximo->peso, vertices[12].listaAdj->proximo->peso, vertices[19].listaAdj->proximo->peso, vertices[26].listaAdj->proximo->peso, vertices[33].listaAdj->proximo->peso, vertices[40].listaAdj->proximo->peso, vertices[47].listaAdj->proximo->peso, vertices[54].listaAdj->proximo->peso, vertices[60].listaAdj->proximo->peso,
    vertices[2].listaAdj->peso, vertices[6].listaAdj->peso, vertices[12].listaAdj->peso, vertices[19].listaAdj->peso, vertices[26].listaAdj->peso, vertices[33].listaAdj->peso, vertices[40].listaAdj->peso, vertices[47].listaAdj->peso, vertices[54].listaAdj->peso, vertices[60].listaAdj->peso, vertices[64].listaAdj->peso,
    vertices[3].listaAdj->peso, vertices[7].listaAdj->proximo->peso, vertices[13].listaAdj->proximo->peso, vertices[20].listaAdj->proximo->peso, vertices[27].listaAdj->proximo->peso, vertices[34].listaAdj->proximo->peso, vertices[41].listaAdj->proximo->peso, vertices[48].listaAdj->proximo->peso, vertices[55].listaAdj->proximo->peso, vertices[61].listaAdj->proximo->peso, 
    vertices[7].listaAdj->peso, vertices[13].listaAdj->peso, vertices[20].listaAdj->peso, vertices[27].listaAdj->peso, vertices[34].listaAdj->peso, vertices[41].listaAdj->peso, vertices[48].listaAdj->peso, vertices[55].listaAdj->peso, vertices[61].listaAdj->peso, 
    vertices[8].listaAdj->peso, vertices[14].listaAdj->proximo->peso, vertices[21].listaAdj->proximo->peso, vertices[28].listaAdj->proximo->peso, vertices[35].listaAdj->proximo->peso, vertices[42].listaAdj->proximo->peso, vertices[49].listaAdj->proximo->peso, vertices[56].listaAdj->proximo->peso, 
    vertices[14].listaAdj->peso, vertices[21].listaAdj->peso, vertices[28].listaAdj->peso, vertices[35].listaAdj->peso, vertices[42].listaAdj->peso, vertices[49].listaAdj->peso, vertices[56].listaAdj->peso, 
    vertices[15].listaAdj->peso, vertices[22].listaAdj->proximo->peso, vertices[29].listaAdj->proximo->peso, vertices[36].listaAdj->proximo->peso,  vertices[43].listaAdj->proximo->peso, vertices[50].listaAdj->proximo->peso);

    printf("\tA energia gasta por Hercules de 0 ate %d foi: %d\n", destino, vertices[destino].peso);
    interacaoComUsuario(anteriorOrdenado, tamanho, destino);
    
    liberarListaAdjacencia(vertices, tamanho, anteriorOrdenado);
}

void opcao3(int op) {
    Vertice *vertices;
    int tamanho, origem, destino;
    int* anteriorOrdenado;

    FILE* fp = fopen("Grafo.txt", "r");

    if (fp == NULL) {
        printf("\tErro ao abrir o arquivo\n");
        exit(1);
    }

    fscanf(fp, "%d", &tamanho);

    anteriorOrdenado = (int*)malloc(sizeof(int) * tamanho);
    vertices = (Vertice*)malloc(sizeof(Vertice) * tamanho);

    lerGrafo(fp, vertices, tamanho, &origem, &destino, op);

    printf("\n");
    dijkstra(vertices, tamanho, origem, destino, anteriorOrdenado, op);

    printf(
    "\t                                                               \n"
    "\t              |01| -- %d  -- |04| -- %d  -- |07|               \n"
    "\t               |             |             |                   \n"
    "\t               %d             %d             %d                \n"
    "\t               |             |             |                   \n"
    "\t|00| -- %d  -- |02| -- %d  -- |05| -- %d  -- |08| -- %d -- |10|\n"
    "\t               |             |             |                   \n"
    "\t               %d             %d             %d                \n"
    "\t               |             |             |                   \n"
    "\t              |03| -- %d  -- |06| -- %d  -- |09|               \n"
    "\t                                                               \n", 
    vertices[1].listaAdj->peso, vertices[4].listaAdj->peso, 
    vertices[1].listaAdj->proximo->peso, vertices[4].listaAdj->proximo->peso, vertices[7].listaAdj->peso, 
    vertices[0].listaAdj->peso, vertices[2].listaAdj->peso, vertices[5].listaAdj->peso, vertices[8].listaAdj->peso, 
    vertices[3].listaAdj->proximo->peso, vertices[5].listaAdj->proximo->peso, vertices[9].listaAdj->peso, 
    vertices[3].listaAdj->peso, vertices[6].listaAdj->peso);

    liberarListaAdjacencia(vertices, tamanho, anteriorOrdenado);
}