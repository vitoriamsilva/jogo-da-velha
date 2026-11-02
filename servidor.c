
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <winsock2.h>
#include <ws2tcpip.h>

#define PORTA 8080
#define TAM_BUFFER 1024

int main(void) {
    WSADATA dados;
    SOCKET servidor_fd, cliente_fd;
    struct sockaddr_in endereco;
    int endereco_len = sizeof(endereco);

    char buffer[TAM_BUFFER];

    if (WSAStartup(MAKEWORD(2, 2), &dados) != 0) {
        printf("Erro ao iniciar Winsock!\n");
        return 1;
    }

    servidor_fd = socket(AF_INET, SOCK_STREAM, 0);

    if (servidor_fd == INVALID_SOCKET) {
        printf("Erro ao criar socket!\n");
        WSACleanup();
        return 1;
    }

    endereco.sin_family = AF_INET;
    endereco.sin_addr.s_addr = INADDR_ANY;
    endereco.sin_port = htons(PORTA);

    if (bind(servidor_fd, (struct sockaddr *)&endereco, sizeof(endereco)) == SOCKET_ERROR) {
        printf("Erro no bind!\n");
        closesocket(servidor_fd);
        WSACleanup();
        return 1;
    }

    if (listen(servidor_fd, 1) == SOCKET_ERROR) {
        printf("Erro no listen!\n");
        closesocket(servidor_fd);
        WSACleanup();
        return 1;
    }

    printf("Servidor aguardando conexao na porta %d...\n", PORTA);

    cliente_fd = accept(servidor_fd, (struct sockaddr *)&endereco, &endereco_len);

    if (cliente_fd == INVALID_SOCKET) {
        printf("Erro no accept!\n");
        closesocket(servidor_fd);
        WSACleanup();
        return 1;
    }

    printf("Cliente conectado!\n");

    while (1) {
        memset(buffer, 0, TAM_BUFFER);

        int bytes = recv(cliente_fd, buffer, TAM_BUFFER - 1, 0);

        if (bytes <= 0) {
            printf("Cliente desconectou.\n");
            break;
        }

        printf("\nCliente: %s\n", buffer);

        if (strcmp(buffer, "sair") == 0)
            break;

        printf("Servidor: ");
        fgets(buffer, TAM_BUFFER, stdin);

        buffer[strcspn(buffer, "\n")] = '\0';

        send(cliente_fd, buffer, (int)strlen(buffer) + 1, 0);

        if (strcmp(buffer, "sair") == 0)
            break;
    }

    closesocket(cliente_fd);
    closesocket(servidor_fd);
    WSACleanup();

    return 0;
}
