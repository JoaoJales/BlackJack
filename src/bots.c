#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "bots.h"
#include "baralho.h"
#include "utils.h"
#include "interfaces.h"

void distribuicao_cartas_iniciais_bots(BotsInfo bots[], int num_bots){
    for (int i = 0; i < num_bots; i++) {
        bots[i].cartas[0] = comprar_carta();
        bots[i].cartas[1] = comprar_carta();
        bots[i].num_cartas = 2;
        
    }
    tela_cartas_iniciais_bot(bots, num_bots);
}

void inicializar_bots(BotsInfo bots[], int n) {
    for (int i = 0; i < n; i++) {
        snprintf(bots[i].nome, sizeof(bots[i].nome), "Bot %d", i + 2);
        bots[i].saldo = 100.0;
        bots[i].num_cartas = 0;
        bots[i].terminou = 0;
    }
}

void* rotina_bot(void* arg) {
    BotsInfo* bot = (BotsInfo*)arg;

    system("clear");
    printf("\t┌────────────────────────────────────┐\n");
    printf("\t \t🤖 %s está jogando...\n\n", bot->nome);
    printf("\t");
    imprimir_cartas(bot->cartas, bot->num_cartas, 0);
    printf("\t└────────────────────────────────────┘\n\n");

    sleep(1);

    while (1) {
        int pontuacao = calcular_pontuacao(bot->cartas, bot->num_cartas);
        printf("\t----------------------------------------------\n");
        if (pontuacao > 21) {
            printf("\t     💥 %s estourou com %d pontos!\n", bot->nome, pontuacao);
            printf("\t----------------------------------------------\n");
            sleep(2);
            break;
        }
        
        if (pontuacao >= 17) {
            printf("\t    🛑 %s decidiu parar com %d pontos.\n", bot->nome, pontuacao);
            printf("\t----------------------------------------------\n");
            sleep(2);
            break;
        }


        int nova_carta = comprar_carta();
        bot->cartas[bot->num_cartas] = nova_carta;
        bot->num_cartas++;

        printf("\t\t🤖 comprou: ");
        imprimir_uma_carta(nova_carta);
        printf("\n\t");
        imprimir_cartas(bot->cartas, bot->num_cartas, 0);
        printf("\t----------------------------------------------\n");


        sleep(3);
    }

    bot->terminou = 1;

    // Retorna a pontuação final do bot
    int* resultado = malloc(sizeof(int));
    *resultado = calcular_pontuacao(bot->cartas, bot->num_cartas);
    pthread_exit((void*)resultado);
}