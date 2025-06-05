#ifndef BOTS_H
#define BOTS_H

#include "jogador.h"

#define NUM_BOTS 2

typedef struct {
    char nome[50];
    int cartas[MAX_CARTAS];
    int num_cartas;
    int terminou;
    double saldo;
} BotsInfo;

void distribuicao_cartas_iniciais_bots(BotsInfo bots[], int num_bots);
void inicializar_bots(BotsInfo bots[], int n);
void* rotina_bot(void* arg);

#endif