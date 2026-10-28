#include "jogador_ia.h"
#include "tabuleiro.h"

int contaVitorias(int m[3][3], int jogador) {
    int i, j;
    int total = 0;

    for (i = 0; i < 3; i++) {
        for (j = 0; j < 3; j++) {
            if (m[i][j] == 0) {
                m[i][j] = jogador;

                if (temVencedor(m) == jogador * 3)
                    total++;

                m[i][j] = 0;
            }
        }
    }

    return total;
}

void jogaIA(int m[3][3], int jogador) {
    int i, j, outro;
    int linha, coluna;
    int possibilidades;
    int cantos[4][2] = {{0, 0}, {0, 2}, {2, 0}, {2, 2}};
    int opostos[4][2] = {{2, 2}, {2, 0}, {0, 2}, {0, 0}};

    if (jogador == 1)
        outro = 4;
    else
        outro = 1;

    for (i = 0; i < 3; i++) {
        for (j = 0; j < 3; j++) {
            if (m[i][j] == 0) {
                m[i][j] = jogador;

                if (temVencedor(m) == jogador * 3)
                    return;

                m[i][j] = 0;
            }
        }
    }

    for (i = 0; i < 3; i++) {
        for (j = 0; j < 3; j++) {
            if (m[i][j] == 0) {
                m[i][j] = outro;

                if (temVencedor(m) == outro * 3) {
                    m[i][j] = jogador;
                    return;
                }

                m[i][j] = 0;
            }
        }
    }

    for (i = 0; i < 3; i++) {
        for (j = 0; j < 3; j++) {
            if (m[i][j] == 0) {
                m[i][j] = jogador;
                possibilidades = contaVitorias(m, jogador);
                m[i][j] = 0;

                if (possibilidades >= 2) {
                    m[i][j] = jogador;
                    return;
                }
            }
        }
    }

    if (m[1][1] == 0) {
        m[1][1] = jogador;
        return;
    }

    for (i = 0; i < 4; i++) {
        linha = cantos[i][0];
        coluna = cantos[i][1];

        if (m[linha][coluna] == outro &&
            m[opostos[i][0]][opostos[i][1]] == 0) {
            m[opostos[i][0]][opostos[i][1]] = jogador;
            return;
        }
    }

    for (i = 0; i < 4; i++) {
        linha = cantos[i][0];
        coluna = cantos[i][1];

        if (m[linha][coluna] == 0) {
            m[linha][coluna] = jogador;
            return;
        }
    }

    for (i = 0; i < 3; i++) {
        for (j = 0; j < 3; j++) {
            if (m[i][j] == 0) {
                m[i][j] = jogador;
                return;
            }
        }
    }
}