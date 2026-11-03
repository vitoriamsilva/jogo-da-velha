# Jogo da Velha em C

Trabalho de Programação Estruturada.
Autores: Vitória Maria e Gustavo Borges

O jogo tem tres modos: humano x humano, humano x IA e jogador remoto (servidor e cliente).

## Como compilar (Windows, gcc)

Jogo local (humano x humano e humano x IA):

    gcc main.c partida.c tabuleiro.c jogador_teclado.c jogador_ia.c -o jogo

Jogo remoto:

    gcc main_servidor.c partida_remota.c jogador_remoto.c tabuleiro.c jogador_teclado.c -o servidor -lws2_32
    gcc main_cliente.c partida_remota.c jogador_remoto.c tabuleiro.c jogador_teclado.c -o cliente -lws2_32

## Como jogar

Jogo local: rode `jogo` e escolha a opcao 1 (humano x humano) ou 2 (humano x IA).

Jogo remoto:
1. Rode `servidor` e digite uma porta (ex: 8080). Ele joga como X e comeca.
2. Em outro terminal (ou outro computador), rode `cliente`, digite o IP do servidor
   (127.0.0.1 se for no mesmo computador) e a mesma porta. Ele joga como O.

## Arquivos

- `tabuleiro.c/.h`: matriz 3x3, desenho, vencedor e jogada
- `jogador_teclado.c/.h`: jogada digitada pelo usuario
- `jogador_ia.c/.h`: jogador do computador (regras R1 a R6)
- `jogador_remoto.c/.h`: sockets (servidor, cliente, envio e recebimento de jogada)
- `partida.c/.h`: partidas locais
- `partida_remota.c/.h`: partida do servidor e do cliente
- `main.c`, `main_servidor.c`, `main_cliente.c`: programas principais

## Tabuleiro

A matriz guarda 0 (vazio), 1 (O) e 4 (X). Somando uma linha, 3 significa tres O e 12 significa tres X.