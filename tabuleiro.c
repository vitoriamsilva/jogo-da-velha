#include <stdio.h>
#include "tabuleiro.h"

void iniciaTabuleiro(int m[3][3]) {
    int i, j;

    for (i = 0; i < 3; i++) {
        for (j = 0; j < 3; j++) {
            m[i][j] = 0;
        }
    }
}

void desenha(int m[3][3]) {
    int i, j;

    printf("\033[2J\033[H");
    printf("\n");

    for (i = 0; i < 3; i++) {
        for (j = 0; j < 3; j++) {
            if (m[i][j] == 1)
                printf(" O ");
            else if (m[i][j] == 4)
                printf(" X ");
            else
                printf("   ");

            if (j < 2)
                printf("|");
        }

        printf("\n");

        if (i < 2)
            printf("---+---+---\n");
    }

    printf("\n");
}

int temVencedor(int m[3][3]) {
    int i, soma;

    for (i = 0; i < 3; i++) {
        soma = m[i][0] + m[i][1] + m[i][2];

        if (soma == 3 || soma == 12)
            return soma;

        soma = m[0][i] + m[1][i] + m[2][i];

        if (soma == 3 || soma == 12)
            return soma;
    }

    soma = m[0][0] + m[1][1] + m[2][2];

    if (soma == 3 || soma == 12)
        return soma;

    soma = m[0][2] + m[1][1] + m[2][0];

    if (soma == 3 || soma == 12)
        return soma;

    return 0;
}

int marcaJogada(int m[3][3], int linha, int coluna, int jogador) {
    if (linha < 1 || linha > 3 || coluna < 1 || coluna > 3)
        return 0;

    if (m[linha - 1][coluna - 1] != 0)
        return 0;

    m[linha - 1][coluna - 1] = jogador;

    return 1;
}