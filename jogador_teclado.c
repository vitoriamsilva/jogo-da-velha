#include <stdio.h>
#include "jogador_teclado.h"
#include "tabuleiro.h"

void jogaTeclado(int m[3][3], int jogador) {
    int linha, coluna;
    int marcou = 0;

    while (marcou == 0) {
        if (jogador == 1)
            printf("Jogador O\n");
        else
            printf("Jogador X\n");

        printf("Digite a linha (1 a 3): ");
        scanf("%d", &linha);

        printf("Digite a coluna (1 a 3): ");
        scanf("%d", &coluna);

        if (linha < 1 || linha > 3 || coluna < 1 || coluna > 3) {
            printf("Posicao invalida!\n");
        } else if (m[linha - 1][coluna - 1] != 0) {
            printf("Essa casa ja esta ocupada!\n");
        } else {
            marcou = marcaJogada(m, linha, coluna, jogador);
        }
    }
}