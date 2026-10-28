
#include <stdio.h>

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

void joga(int m[3][3], int jogador) {
    int linha, coluna;

    do {
        printf("Jogador %c\n", jogador == 1 ? 'O' : 'X');
        printf("Digite a linha (1 a 3): ");
        scanf("%d", &linha);
        printf("Digite a coluna (1 a 3): ");
        scanf("%d", &coluna);

        if (linha < 1 || linha > 3 ||
            coluna < 1 || coluna > 3) {
            printf("Posicao invalida!\n");
        } else if (m[linha - 1][coluna - 1] != 0) {
            printf("Essa casa ja esta ocupada!\n");
        } else {
            break;
        }
    } while (1);

    m[linha - 1][coluna - 1] = jogador;
}

int main() {
    int m[3][3] = {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}};
    int jogador = 1;
    int jogadas = 0;
    int vencedor = 0;

    while (jogadas < 9 && vencedor == 0) {
        desenha(m);
        joga(m, jogador);
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

    return 0;
}
