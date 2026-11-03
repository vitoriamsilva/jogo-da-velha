#ifndef TABULEIRO_H
#define TABULEIRO_H

#define JOGADOR_O 1
#define JOGADOR_X 4
#define VENCEU_O 3
#define VENCEU_X 12

void iniciaTabuleiro(int m[3][3]);
void desenha(int m[3][3]);
int temVencedor(int m[3][3]);
int marcaJogada(int m[3][3], int linha, int coluna, int jogador);

#endif