#ifndef JOGO_H
#define JOGO_H

#include "jogador.h"
#include "dealer.h"

void game(JogadorInfo* jogador);
double aposta(JogadorInfo* jogador);
void distribuicao_cartas_iniciais_dealer(DealerInfo* dealer);
void distribuicao_cartas_iniciais_jogador(JogadorInfo* jogador);
void pontuacao_final(int pont_dealer, int pont_jogador, JogadorInfo* jogador, double aposta);


#endif