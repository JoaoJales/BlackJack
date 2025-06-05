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
    printf("\n\t----------------------------------------------\n");
    printf("\t          🃏 2º carta da Casa: ");
    imprimir_uma_carta(dealerInfo->cartas[0]);
    printf("\n");

    imprimir_cartas("Casa", dealerInfo->cartas, dealerInfo->num_cartas, 0);
    sleep(2);

    printf("\t----------------------------------------------\n");
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

        
        printf("\t             Casa comprou: ");
        imprimir_uma_carta(nova_carta);
        printf("\t----------------------------------------------\n");
        imprimir_cartas("Casa", dealerInfo->cartas, dealerInfo->num_cartas, 0);
        sleep(3);
    }
    
    sleep(5);

    int* resultado = malloc(sizeof(int));
    *resultado = calcular_pontuacao(dealerInfo->cartas, dealerInfo->num_cartas);
    pthread_exit((void*)resultado);
}
