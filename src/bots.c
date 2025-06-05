#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "bots.h"
#include "baralho.h"
#include "utils.h"

void distribuicao_cartas_iniciais_bots(BotsInfo bots[], int num_bots){
    printf("\t----------------------------------------------\n");

    for (int i = 0; i < num_bots; i++) {
            bots[i].cartas[0] = comprar_carta();
            bots[i].cartas[1] = comprar_carta();
            bots[i].num_cartas = 2;
            
            printf("\t          🃏 cartas iniciais %s:            \n", bots[i].nome);
            imprimir_cartas(bots[i].nome, bots[i].cartas, bots[i].num_cartas, 0);
            printf("\t----------------------------------------------\n");
            sleep(1);
    }
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
    printf("\t----------------------------------------------\n");
    printf("\t          🤖 %s está jogando...\n", bot->nome);
    imprimir_cartas(bot->nome, bot->cartas, bot->num_cartas, 0);
    printf("\t----------------------------------------------\n\n");

    sleep(1);

    while (1) {
        int pontuacao = calcular_pontuacao(bot->cartas, bot->num_cartas);

        if (pontuacao > 21) {
            printf("\n\t     💥 %s estourou com %d pontos!\n", bot->nome, pontuacao);
            printf("\t----------------------------------------------\n");
            sleep(2);
            break;
        }
        
        if (pontuacao >= 17) {
            printf("\n\t    🛑 %s decidiu parar com %d pontos.\n", bot->nome, pontuacao);
            printf("\t----------------------------------------------\n");
            sleep(2);
            break;
        }


        int nova_carta = comprar_carta();
        bot->cartas[bot->num_cartas] = nova_carta;
        bot->num_cartas++;

        printf("\t\t🤖 comprou: ");
        imprimir_uma_carta(nova_carta);
        imprimir_cartas(bot->nome, bot->cartas, bot->num_cartas, 0);
        printf("\t----------------------------------------------\n");


        sleep(3);
    }

    bot->terminou = 1;

    // Retorna a pontuação final do bot
    int* resultado = malloc(sizeof(int));
    *resultado = calcular_pontuacao(bot->cartas, bot->num_cartas);
    pthread_exit((void*)resultado);
}