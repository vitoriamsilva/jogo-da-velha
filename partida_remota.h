#ifndef PARTIDA_REMOTA_H
#define PARTIDA_REMOTA_H

#include <winsock2.h>

void partidaServidor(SOCKET conexao);
void partidaCliente(SOCKET conexao);

#endif