#include <stdio.h>
#include "partida.h"

int main(void) {
    int opcao = 0;
    int c;

    while (opcao != 1 && opcao != 2) {
        printf("=== JOGO DA VELHA ===\n\n");
        printf("1 - Humano x Humano\n");
        printf("2 - Humano x IA\n\n");
        printf("Escolha uma opcao: ");

        if (scanf("%d", &opcao) != 1) {
            opcao = 0;
            while ((c = getchar()) != '\n' && c != EOF)
                ;
        }

        if (opcao != 1 && opcao != 2)
            printf("\nOpcao invalida!\n\n");
    }

    if (opcao == 1)
        partidaHumanoHumano();
    else
        partidaHumanoIA();

    return 0;
}