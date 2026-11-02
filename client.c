
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <winsock2.h>
#include <ws2tcpip.h>

#define PORTA 8080
#define TAM_BUFFER 1024

int main(void) {
    WSADATA dados;
    SOCKET sock;
    struct sockaddr_in servidor;
    char buffer[TAM_BUFFER];

    if (WSAStartup(MAKEWORD(2, 2), &dados) != 0) {
        printf("Erro ao iniciar Winsock!\n");
        return 1;
    }

    sock = socket(AF_INET, SOCK_STREAM, 0);

    if (sock == INVALID_SOCKET) {
        printf("Erro ao criar socket!\n");
        WSACleanup();
        return 1;
    }

    servidor.sin_family = AF_INET;
    servidor.sin_port = htons(PORTA);

    if (inet_pton(AF_INET, "127.0.0.1", &servidor.sin_addr) <= 0) {
        printf("Endereco invalido!\n");
        closesocket(sock);
        WSACleanup();
        return 1;
    }

    if (connect(sock, (struct sockaddr *)&servidor, sizeof(servidor)) == SOCKET_ERROR) {
        printf("Erro ao conectar!\n");
        closesocket(sock);
        WSACleanup();
        return 1;
    }

    printf("Conectado ao servidor!\n");

    while (1) {
        printf("Cliente: ");
        fgets(buffer, TAM_BUFFER, stdin);

        buffer[strcspn(buffer, "\n")] = '\0';

        send(sock, buffer, (int)strlen(buffer) + 1, 0);

        if (strcmp(buffer, "sair") == 0)
            break;

        memset(buffer, 0, TAM_BUFFER);

        int bytes = recv(sock, buffer, TAM_BUFFER - 1, 0);

        if (bytes <= 0) {
            printf("Servidor desconectou.\n");
            break;
        }

        printf("Servidor: %s\n", buffer);

        if (strcmp(buffer, "sair") == 0)
            break;
    }

    closesocket(sock);
    WSACleanup();

    return 0;
}
