#include <stdio.h>
#include "jogador_teclado.h"
#include "tabuleiro.h"

void jogaTeclado(int m[3][3], int jogador, int *linha, int *coluna) {
    int marcou = 0;

    while (marcou == 0) {
        if (jogador == JOGADOR_O)
            printf("Jogador O\n");
        else
            printf("Jogador X\n");

        printf("Digite a linha (1 a 3): ");
        scanf("%d", linha);

        printf("Digite a coluna (1 a 3): ");
        scanf("%d", coluna);

        marcou = marcaJogada(m, *linha, *coluna, jogador);

        if (marcou == 0)
            printf("Jogada invalida! Escolha uma casa vazia de 1 a 3.\n");
    }
}