#include <stdio.h>
#include <winsock2.h>
#include "partida_remota.h"
#include "jogador_remoto.h"

int main(void) {
    WSADATA dados;
    SOCKET conexao;
    char ip[20];
    int porta;

    if (WSAStartup(MAKEWORD(2, 2), &dados) != 0) {
        printf("Erro ao iniciar Winsock!\n");
        return 1;
    }

    printf("=== JOGO DA VELHA REMOTO ===\n");
    printf("Voce sera o jogador O.\n\n");

    printf("IP do servidor (127.0.0.1 se for neste computador): ");
    scanf("%19s", ip);

    printf("Porta (a mesma do servidor): ");
    scanf("%d", &porta);

    conexao = conectaServidor(ip, porta);

    if (conexao == INVALID_SOCKET) {
        WSACleanup();
        return 1;
    }

    partidaCliente(conexao);

    fechaConexao(conexao);
    WSACleanup();

    return 0;
}