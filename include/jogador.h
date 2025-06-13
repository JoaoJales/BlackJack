#ifndef JOGADOR_H
#define JOGADOR_H

#include <pthread.h>

#define MAX_CARTAS 12
typedef struct {
    char nome[50];
    int cartas[MAX_CARTAS];
    int num_cartas;
    double saldo;
    int ativo;
} JogadorInfo;

JogadorInfo criarJogador(); 
void* rotina_jogador(void* arg);

#endif