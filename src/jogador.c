#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <unistd.h>
#include "jogador.h"
#include "baralho.h"
#include "utils.h"

JogadorInfo criarJogador() {
    JogadorInfo jogador;
    printf("\tDigite o seu nome: ");
    fgets(jogador.nome, sizeof(jogador.nome), stdin);
    jogador.nome[strcspn(jogador.nome, "\n")] = '\0';
    jogador.num_cartas = 0;
    jogador.saldo = 100.00;

    sleep(1);
    return jogador;
}

void* rotina_jogador(void* arg) {
    JogadorInfo* jogador = (JogadorInfo*)arg;

    
    while (1) {
        int pontuacao = calcular_pontuacao(jogador->cartas, jogador->num_cartas);

        if (pontuacao > 21) {
            printf("\n\t----------------------------------------------\n");
            printf("\t💥 Você estourou com %d pontos!\n", pontuacao);
            printf("\n\t----------------------------------------------\n");
            sleep(5);
            break;
        }
        
        char resposta[4];
        if (pontuacao < 21)
        {
            printf("\n\t %s, deseja comprar mais uma carta? (s/n): ", jogador->nome);
            fgets(resposta, sizeof(resposta), stdin);
        }else{
            strcpy(resposta, "n");
        }
        

        printf("\n\t----------------------------------------------\n");
        if (resposta[0] == 's' || resposta[0] == 'S') {
            int nova_carta = comprar_carta();
            jogador->cartas[jogador->num_cartas] = nova_carta;
            jogador->num_cartas++;


            printf("\t            🃏 Você comprou: ");
            imprimir_uma_carta(nova_carta);
            printf("\t----------------------------------------------\n");

            imprimir_cartas(jogador->nome, jogador->cartas, jogador->num_cartas, 0);
        } else {
            printf("\t  🛑 %s decidiu parar com %d pontos.\n", jogador->nome, pontuacao);
            printf("\t----------------------------------------------\n");
            sleep(4);
            break;
        }
    }

    // Retorna a pontuação final
    int* resultado = malloc(sizeof(int));
    *resultado = calcular_pontuacao(jogador->cartas, jogador->num_cartas);
    pthread_exit((void*)resultado);
}