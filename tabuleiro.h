#ifndef TABULEIRO_H
#define TABULEIRO_H

void iniciaTabuleiro(int m[3][3]);
void desenha(int m[3][3]);
int temVencedor(int m[3][3]);
int marcaJogada(int m[3][3], int linha, int coluna, int jogador);

#endif