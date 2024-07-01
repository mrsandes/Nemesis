#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "Grafo.h"
#include "Grafo.c"

#define MAX_STRING 50
#define SUCESSO 0

int main() {
    int op;
    char nomeArquivo[MAX_STRING];

    printf("ola!\n");

    do {
        do {    
            printf(
                "\n1 - Calcular caminho mais rapido do seu grafo  \n"
                "2 - Jogar                                        \n"
                "3 - Testar funcionamento do codigo               \n"
                "4 - Limpar terminal                              \n"
                "0 - Sair                                         \n");
            printf("Digite a opcao desejada: ");
            scanf("%d", &op);
            getchar();

            if (op < 0 || op > 4) {
                printf("Digite uma opcao valida\n");
            }
        } while (op < 0 && op > 4);

        switch (op) {
        case 0:
            break;

        case 1:
            printf(
                "\n\tO formato do arquivo txt deve ser:                                                                                     \n"
                "\t1: (numero de vertices)                                                                                                  \n"
                "\t2: (origem) (destino) (peso)                                                                                             \n"
                "\t3 ... : mesmo formato da linha 2 porem com os valores diferentes                                                         \n"
                "\n\tOBS:                                                                                                                   \n"
                "\tO grafo não deve ser orientado pois o codigo ja cria um caminho de ida e volta para o vertice descrito                   \n"
                "\tPortanto, evite repetir um ligação entre 2 vertices diferentes pois o programa ira utilizar a com o menor peso           \n");
            printf("\n\tDigite o nome do arquivo: ");
            fgets(nomeArquivo, MAX_STRING, stdin);

            for (int i = 0; i < MAX_STRING; i++) {
                if (nomeArquivo[i] == '\n') {
                    nomeArquivo[i] = '\0';
                }
            }
            
            opcao1(op, nomeArquivo);
            break;
        
        case 2:
            opcao2(op);
            break;

        case 3:
            opcao3(op);
            break;

        case 4:
            system("clear");
            system("cls");
            printf("ola!\n");
            break;
        }
    } while (op != 0);

    return SUCESSO;
}