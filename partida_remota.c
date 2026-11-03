#include <stdio.h>
#include "partida_remota.h"
#include "tabuleiro.h"
#include "jogador_teclado.h"
#include "jogador_remoto.h"

void partidaServidor(SOCKET conexao) {
    int m[3][3];
    int linha, coluna;
    int jogadas = 0;
    int status = 0;

    iniciaTabuleiro(m);

    while (jogadas < 9 && status == 0) {
        desenha(m);

        jogaTeclado(m, JOGADOR_X, &linha, &coluna);
        jogadas++;

        status = temVencedor(m);

        if (status == 0 && jogadas == 9)
            status = 1;

        if (enviaJogada(conexao, linha, coluna, status) == 0) {
            printf("Erro ao enviar jogada!\n");
            return;
        }

        desenha(m);

        if (status != 0)
            break;

        printf("Aguardando jogada do jogador O...\n");

        if (recebeJogada(conexao, &linha, &coluna, &status) == 0) {
            printf("Erro ao receber jogada!\n");
            return;
        }

        if (marcaJogada(m, linha, coluna, JOGADOR_O) == 0) {
            printf("Jogada recebida invalida!\n");
            return;
        }

        jogadas++;
        desenha(m);
    }

    if (status == VENCEU_X)
        printf("O jogador X venceu!\n");
    else if (status == VENCEU_O)
        printf("O jogador O venceu!\n");
    else
        printf("Deu empate!\n");
}

void partidaCliente(SOCKET conexao) {
    int m[3][3];
    int linha, coluna;
    int jogadas = 0;
    int status = 0;

    iniciaTabuleiro(m);

    while (jogadas < 9 && status == 0) {
        printf("Aguardando jogada do jogador X...\n");

        if (recebeJogada(conexao, &linha, &coluna, &status) == 0) {
            printf("Erro ao receber jogada!\n");
            return;
        }

        if (marcaJogada(m, linha, coluna, JOGADOR_X) == 0) {
            printf("Jogada recebida invalida!\n");
            return;
        }

        jogadas++;
        desenha(m);

        if (status != 0)
            break;

        jogaTeclado(m, JOGADOR_O, &linha, &coluna);
        jogadas++;

        status = temVencedor(m);

        if (status == 0 && jogadas == 9)
            status = 1;

        if (enviaJogada(conexao, linha, coluna, status) == 0) {
            printf("Erro ao enviar jogada!\n");
            return;
        }

        desenha(m);
    }

    mostraResultado(status);

}