#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include "dealer.h"
#include "baralho.h"
#include "utils.h"
#include "jogador.h"


void* rotina_dealer(void* arg) {
    DealerInfo* dealerInfo = (DealerInfo*)arg;
    system("clear");
    printf("\t-----------------------------------------------\n");
    printf("\t|             Casa está jogando...               |\n");
    printf("\t-----------------------------------------------\n");

    printf("\n\t┌────────────────────────────────────────┐\n");
    printf("\t\t🃏 2º carta da Casa: ");
    imprimir_uma_carta(dealerInfo->cartas[0]);
    printf("\n");
    printf("\t");
    imprimir_cartas(dealerInfo->cartas, dealerInfo->num_cartas, 0);
    printf("\t└────────────────────────────────────────┘\n");

    sleep(3);



    printf("\n\t----------------------------------------------\n");

    while (1)
    {
        int pontuacao = calcular_pontuacao(dealerInfo->cartas, dealerInfo->num_cartas);
        
        if (pontuacao > 21)
        {
            printf("\n\t     💥 Casa estourou com %d pontos!\n", pontuacao);
            printf("\t----------------------------------------------\n");
            break;
        }

        if (pontuacao >= 17)
        {
            printf("\n\t  🛑 Casa decidiu parar com %d pontos.\n", pontuacao);
            printf("\t----------------------------------------------\n");
            sleep(2);
            break;
        }
        
        
        
        int nova_carta = comprar_carta();
        dealerInfo->cartas[dealerInfo->num_cartas] = nova_carta;
        dealerInfo->num_cartas++;

        
        printf("\t\tCasa comprou: ");
        imprimir_uma_carta(nova_carta);
        printf("\n\t");
        imprimir_cartas(dealerInfo->cartas, dealerInfo->num_cartas, 0);
        printf("\t----------------------------------------------\n");

        sleep(3);
    }
    
    sleep(4);

    int* resultado = malloc(sizeof(int));
    *resultado = calcular_pontuacao(dealerInfo->cartas, dealerInfo->num_cartas);
    pthread_exit((void*)resultado);
}
