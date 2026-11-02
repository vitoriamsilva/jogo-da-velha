#ifndef JOGADOR_REMOTO_H
#define JOGADOR_REMOTO_H

#include <winsock2.h>

SOCKET iniciaServidor(int porta);
SOCKET conectaServidor(char ip[], int porta);

int enviaJogada(SOCKET conexao, int linha, int coluna, int status);
int recebeJogada(SOCKET conexao, int *linha, int *coluna, int *status);

void fechaConexao(SOCKET conexao);

#endif