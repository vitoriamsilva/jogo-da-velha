#include <stdio.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include "jogador_remoto.h"

SOCKET iniciaServidor(int porta) {
    SOCKET servidor, cliente;
    struct sockaddr_in endereco;
    int tamanho = sizeof(endereco);

    servidor = socket(AF_INET, SOCK_STREAM, 0);

    if (servidor == INVALID_SOCKET) {
        printf("Erro ao criar socket!\n");
        return INVALID_SOCKET;
    }

    endereco.sin_family = AF_INET;
    endereco.sin_addr.s_addr = INADDR_ANY;
    endereco.sin_port = htons(porta);

    if (bind(servidor, (struct sockaddr *)&endereco, sizeof(endereco)) == SOCKET_ERROR) {
        printf("Erro no bind!\n");
        closesocket(servidor);
        return INVALID_SOCKET;
    }

    if (listen(servidor, 1) == SOCKET_ERROR) {
        printf("Erro no listen!\n");
        closesocket(servidor);
        return INVALID_SOCKET;
    }

    printf("Aguardando o jogador conectar...\n");

    cliente = accept(servidor, (struct sockaddr *)&endereco, &tamanho);

    closesocket(servidor);

    if (cliente == INVALID_SOCKET) {
        printf("Erro ao aceitar conexao!\n");
        return INVALID_SOCKET;
    }

    printf("Jogador conectado!\n");

    return cliente;
}

SOCKET conectaServidor(char ip[], int porta) {
    SOCKET cliente;
    struct sockaddr_in servidor;

    cliente = socket(AF_INET, SOCK_STREAM, 0);

    if (cliente == INVALID_SOCKET) {
        printf("Erro ao criar socket!\n");
        return INVALID_SOCKET;
    }

    servidor.sin_family = AF_INET;
    servidor.sin_port = htons(porta);

    if (inet_pton(AF_INET, ip, &servidor.sin_addr) <= 0) {
        printf("Endereco IP invalido!\n");
        closesocket(cliente);
        return INVALID_SOCKET;
    }

    if (connect(cliente, (struct sockaddr *)&servidor, sizeof(servidor)) == SOCKET_ERROR) {
        printf("Erro ao conectar ao servidor!\n");
        closesocket(cliente);
        return INVALID_SOCKET;
    }

    printf("Conectado ao servidor!\n");

    return cliente;
}

int enviaJogada(SOCKET conexao, int linha, int coluna, int status) {
    char dados[3];
    int enviados = 0;
    int resultado;

    dados[0] = (char)linha;
    dados[1] = (char)coluna;
    dados[2] = (char)status;

    while (enviados < 3) {
        resultado = send(conexao, dados + enviados, 3 - enviados, 0);

        if (resultado <= 0)
            return 0;

        enviados += resultado;
    }

    return 1;
}

int recebeJogada(SOCKET conexao, int *linha, int *coluna, int *status) {
    char dados[3];
    int recebidos = 0;
    int resultado;

    while (recebidos < 3) {
        resultado = recv(conexao, dados + recebidos, 3 - recebidos, 0);

        if (resultado <= 0)
            return 0;

        recebidos += resultado;
    }

    *linha = dados[0];
    *coluna = dados[1];
    *status = dados[2];

    return 1;
}

void fechaConexao(SOCKET conexao) {
    closesocket(conexao);
}