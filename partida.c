#include <stdio.h>
#include "partida.h"
#include "tabuleiro.h"
#include "jogador_teclado.h"
#include "jogador_ia.h"

void partidaHumanoHumano(void) {
    int m[3][3];
    int jogador = 1;
    int jogadas = 0;
    int vencedor = 0;

    iniciaTabuleiro(m);

    while (jogadas < 9 && vencedor == 0) {
        desenha(m);
        jogaTeclado(m, jogador);
        jogadas++;

        vencedor = temVencedor(m);

        if (jogador == 1)
            jogador = 4;
        else
            jogador = 1;
    }

    desenha(m);

    if (vencedor == 3)
        printf("O jogador O venceu!\n");
    else if (vencedor == 12)
        printf("O jogador X venceu!\n");
    else
        printf("Deu empate!\n");
}

void partidaHumanoIA(void) {
    int m[3][3];
    int jogadas = 0;
    int vencedor = 0;

    iniciaTabuleiro(m);

    while (jogadas < 9 && vencedor == 0) {
        desenha(m);
        jogaTeclado(m, 1);
        jogadas++;

        vencedor = temVencedor(m);

        if (vencedor == 0 && jogadas < 9) {
            jogaIA(m, 4);
            jogadas++;

            vencedor = temVencedor(m);
        }
    }

    desenha(m);

    if (vencedor == 3)
        printf("O jogador venceu!\n");
    else if (vencedor == 12)
        printf("A IA venceu!\n");
    else
        printf("Deu empate!\n");
}