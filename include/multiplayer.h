#ifndef MULTIPLAYER_H
#define MULTIPLAYER_H

#include "jogador.h"
#include "dealer.h"

#define MAX_RODADAS 10
#define MAX_JOGADORES 5

void multiplayer();
void cadastrar_jogadores(JogadorInfo* jogadores);
void apostas(JogadorInfo* jogadores, double* valoresApostas);
void distribuicao_cartas_iniciais_dealer_multiplayer(DealerInfo* dealer);
void distribuicao_cartas_iniciais_jogadores_multiplayer(JogadorInfo* jogadores);
void tela_mesa(JogadorInfo* jogadores, DealerInfo* dealer, int numJogadores, int esconderCartaDealer, double* valoresApostas, int numRodadas, int rodadaAtual);
void resultados_rodada(int pontos_dealer, JogadorInfo* jogadores, double* valoresApostas, int *numJogadoresAtivos);
void resultado_partida(JogadorInfo* jogagores);


#endif