#include "jogador_ia.h"
#include "tabuleiro.h"

static const int CANTOS[4][2]  = {{0, 0}, {0, 2}, {2, 0}, {2, 2}};
static const int OPOSTOS[4][2] = {{2, 2}, {2, 0}, {0, 2}, {0, 0}};

static int contaVitorias(int m[3][3], int jogador) {
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

static int fechaLinha(int m[3][3], int testa, int marca) {
    int i, j;

    for (i = 0; i < 3; i++) {
        for (j = 0; j < 3; j++) {
            if (m[i][j] == 0) {
                m[i][j] = testa;

                if (temVencedor(m) == testa * 3) {
                    m[i][j] = marca;
                    return 1;
                }

                m[i][j] = 0;
            }
        }
    }

    return 0;
}

static int criaGarfo(int m[3][3], int jogador) {
    int i, j;

    for (i = 0; i < 3; i++) {
        for (j = 0; j < 3; j++) {
            if (m[i][j] == 0) {
                m[i][j] = jogador;

                if (contaVitorias(m, jogador) >= 2)
                    return 1;

                m[i][j] = 0;
            }
        }
    }

    return 0;
}

static int jogaCentro(int m[3][3], int jogador) {
    if (m[1][1] == 0) {
        m[1][1] = jogador;
        return 1;
    }

    return 0;
}

static int jogaCantoOposto(int m[3][3], int jogador, int outro) {
    int i;
    int linha, coluna;
    int linhaOposta, colunaOposta;

    for (i = 0; i < 4; i++) {
        linha = CANTOS[i][0];
        coluna = CANTOS[i][1];
        linhaOposta = OPOSTOS[i][0];
        colunaOposta = OPOSTOS[i][1];

        if (m[linha][coluna] == outro && m[linhaOposta][colunaOposta] == 0) {
            m[linhaOposta][colunaOposta] = jogador;
            return 1;
        }
    }

    return 0;
}

static int jogaCantoVazio(int m[3][3], int jogador) {
    int i;
    int linha, coluna;

    for (i = 0; i < 4; i++) {
        linha = CANTOS[i][0];
        coluna = CANTOS[i][1];

        if (m[linha][coluna] == 0) {
            m[linha][coluna] = jogador;
            return 1;
        }
    }

    return 0;
}

static int jogaQualquer(int m[3][3], int jogador) {
    int i, j;

    for (i = 0; i < 3; i++) {
        for (j = 0; j < 3; j++) {
            if (m[i][j] == 0) {
                m[i][j] = jogador;
                return 1;
            }
        }
    }

    return 0;
}

void jogaIA(int m[3][3], int jogador) {
    int outro;

    if (jogador == JOGADOR_O)
        outro = JOGADOR_X;
    else
        outro = JOGADOR_O;

    if (fechaLinha(m, jogador, jogador))
        return;
    if (fechaLinha(m, outro, jogador))
        return;
    if (criaGarfo(m, jogador))
        return;
    if (jogaCentro(m, jogador))
        return;
    if (jogaCantoOposto(m, jogador, outro))
        return;
    if (jogaCantoVazio(m, jogador))
        return;

    jogaQualquer(m, jogador);
}