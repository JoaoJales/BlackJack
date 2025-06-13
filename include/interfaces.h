#ifndef INTERFACE_H
#define INTERFACE_H

#include "jogador.h"
#include "dealer.h"
#include "bots.h"

void limpar_buffer();
JogadorInfo tela_apresentacao();
void tela_Inicial(JogadorInfo jogador);
void tela_como_jogar();
void tela_creditos();
void tela_dados_jogador(JogadorInfo* jogador);
void tela_valor_aposta(double valorAposta);
void tela_embaralhando_cartas();
void tela_1_pontuacao_final(int pont_dealer, int pont_jogador);
void tela_2_pontuacao_final(int* pont_bots, BotsInfo bots[]);
void tela_empate(JogadorInfo* jogador);
void tela_jogador_venceu(JogadorInfo* jogador);
void tela_casa_venceu(JogadorInfo* jogador);
void tela_estourou(JogadorInfo* jogador);
void tela_distribuindo_cartas();
void tela_cartas_iniciais_jogador(JogadorInfo* jogador);
void tela_cartas_iniciais_dealer(DealerInfo* dealer);
void tela_cartas_iniciais_bot(BotsInfo bots[], int numBots);


#endif