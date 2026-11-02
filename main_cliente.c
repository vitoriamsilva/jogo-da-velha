#include <stdio.h>
#include <winsock2.h>
#include "partida_remota.h"
#include "jogador_remoto.h"

#define IP_SERVIDOR "127.0.0.1"

int main(void) {
    WSADATA dados;
    SOCKET conexao;

    if (WSAStartup(MAKEWORD(2, 2), &dados) != 0) {
        printf("Erro ao iniciar Winsock!\n");
        return 1;
    }

    printf("=== JOGO DA VELHA REMOTO ===\n");
    printf("Voce sera o jogador O.\n");

    conexao = conectaServidor(IP_SERVIDOR, 8080);

    if (conexao == INVALID_SOCKET) {
        WSACleanup();
        return 1;
    }

    partidaCliente(conexao);

    fechaConexao(conexao);
    WSACleanup();

    return 0;
}