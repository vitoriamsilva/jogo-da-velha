#include <stdio.h>
#include <winsock2.h>
#include "partida_remota.h"
#include "jogador_remoto.h"

int main(void) {
    WSADATA dados;
    SOCKET conexao;
    int porta;

    if (WSAStartup(MAKEWORD(2, 2), &dados) != 0) {
        printf("Erro ao iniciar Winsock!\n");
        return 1;
    }

    printf("=== JOGO DA VELHA REMOTO ===\n");
    printf("Voce sera o jogador X.\n\n");

    printf("Porta para aguardar conexao (ex: 8080): ");
    scanf("%d", &porta);

    conexao = iniciaServidor(porta);

    if (conexao == INVALID_SOCKET) {
        WSACleanup();
        return 1;
    }

    partidaServidor(conexao);

    fechaConexao(conexao);
    WSACleanup();

    return 0;
}