#include <stdio.h>
#include "partida.h"
#include "tabuleiro.h"
#include "jogador_teclado.h"
#include "jogador_ia.h"

void partidaHumanoHumano(void) {
    int m[3][3];
    int linha, coluna;
    int jogador = JOGADOR_O;
    int jogadas = 0;
    int vencedor = 0;

    iniciaTabuleiro(m);

    while (jogadas < 9 && vencedor == 0) {
        desenha(m);
        jogaTeclado(m, jogador, &linha, &coluna);
        jogadas++;

        vencedor = temVencedor(m);

        if (jogador == JOGADOR_O)
            jogador = JOGADOR_X;
        else
            jogador = JOGADOR_O;
    }

    desenha(m);

    if (vencedor == VENCEU_O)
        printf("O jogador O venceu!\n");
    else if (vencedor == VENCEU_X)
        printf("O jogador X venceu!\n");
    else
        printf("Deu empate!\n");
}

void partidaHumanoIA(void) {
    int m[3][3];
    int linha, coluna;
    int jogadas = 0;
    int vencedor = 0;

    iniciaTabuleiro(m);

    while (jogadas < 9 && vencedor == 0) {
        desenha(m);
        jogaTeclado(m, JOGADOR_O, &linha, &coluna);
        jogadas++;

        vencedor = temVencedor(m);

        if (vencedor == 0 && jogadas < 9) {
            jogaIA(m, JOGADOR_X);
            jogadas++;

            vencedor = temVencedor(m);
        }
    }

    desenha(m);

    if (vencedor == VENCEU_O)
        printf("O jogador venceu!\n");
    else if (vencedor == VENCEU_X)
        printf("A IA venceu!\n");
    else
        printf("Deu empate!\n");
}