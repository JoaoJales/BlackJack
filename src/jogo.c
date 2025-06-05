#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include "jogo.h"
#include "baralho.h"
#include "utils.h"
#include "interfaces.h"
#include "bots.h"


double aposta(JogadorInfo* jogador) {
    system("clear");
    tela_dados_jogador(jogador);
    long int valor_aposta;
    char entrada[100];

    if (jogador->saldo >= 5) {
        while (1) {
            printf("\tQual é o valor da aposta? ");
            if (fgets(entrada, sizeof(entrada), stdin) != NULL) {
                
                if (sscanf(entrada, "%ld", &valor_aposta) == 1) {

                    if (valor_aposta > jogador->saldo) {
                        printf("\tSaldo insuficiente!\n");
                    } else if (valor_aposta < 0) {
                        printf("\tA aposta não pode ser negativa!\n");
                    } else if (valor_aposta < 5) {
                        printf("\tValor mínimo de aposta: R$5\n");
                    } else if (valor_aposta % 5 != 0) {
                        printf("\tA aposta deve ser múltipla de 5!\n");
                    } else {
                        break;
                    }

                } else {
                    printf("\tEntrada inválida!\n");
                }
            }
        }
    } else {
        printf("\t----------------------------------\n");
        printf("\t|            All-in!             |\n");
        printf("\t----------------------------------\n");
        valor_aposta = jogador->saldo;
    }

    if (valor_aposta == jogador->saldo)
    {
        printf("\t----------------------------------\n");
        printf("\t|            All-in!             |\n");
        printf("\t----------------------------------\n");
    }
    
    printf("\n");
    printf("\t--------------------------------------\n");
    printf("\t          Apostando R$%2.lf...        \n", (double)valor_aposta);
    printf("\t---------------------------------------\n");
    sleep(3);

    jogador->saldo -= valor_aposta;
    return (double)valor_aposta;
}

void pontuacao_final(int pont_dealer, int pont_jogador, JogadorInfo* jogador, double aposta){    
    if (pont_jogador > 21) {
        tela_estourou(jogador);

    } else if (pont_dealer > 21 || pont_jogador > pont_dealer) {
        jogador->saldo += aposta * 2;
        tela_jogador_venceu(jogador);

    } else if (pont_jogador == pont_dealer) {
        jogador->saldo += aposta;
        tela_empate(jogador);

    } else {
        tela_casa_venceu(jogador);
    }
    sleep(1);
}

void distribuicao_cartas_iniciais(DealerInfo* dealer, JogadorInfo* jogador){
    dealer->cartas[0] = comprar_carta();
    sleep(1);
    dealer->cartas[1] = comprar_carta();
    dealer->num_cartas = 2;

    sleep(1);
    jogador->cartas[0] = comprar_carta();
    sleep(1);
    jogador->cartas[1] = comprar_carta();
    jogador->num_cartas = 2;

    printf("\t----------------------------------------------\n");
    printf("\t|         🃏 Distribuindo as cartas...       |\n");
    printf("\t----------------------------------------------\n");
    sleep(1);

    printf("\t              🃏 Cartas da Casa:              \n");
    imprimir_cartas("Casa", dealer->cartas, dealer->num_cartas, 1);
    printf("\t----------------------------------------------\n");
    sleep(1);


    printf("\t          🃏 Suas cartas iniciais:            \n");
    imprimir_cartas(jogador->nome, jogador->cartas, jogador->num_cartas, 0);
    printf("\t----------------------------------------------\n\n");
    sleep(1);
}

void game(JogadorInfo* jogador){
    while (1) {
        double valorAposta = aposta(jogador);
        BotsInfo bots[NUM_BOTS];
        DealerInfo dealer;
        
        inicializar_baralho();
        inicializar_bots(bots, NUM_BOTS);

        system("clear");
        tela_dados_jogador(jogador);
        tela_1_game(valorAposta);

        distribuicao_cartas_iniciais(&dealer, jogador);
        distribuicao_cartas_iniciais_bots(bots, NUM_BOTS);

        //Declara as threads
        pthread_t thread_jogador, thread_dealer, threads_bots[NUM_BOTS];

        //Jogador
        pthread_create(&thread_jogador, NULL, rotina_jogador, (void*)jogador);
        void* retorno_jogador;
        pthread_join(thread_jogador, &retorno_jogador);
        int pontuacao_jogador = *(int*)retorno_jogador;
        free(retorno_jogador);


        // Bots
        int pontuacoes_bots[NUM_BOTS];
        for (int i = 0; i < NUM_BOTS; i++) {
            pthread_create(&threads_bots[i], NULL, rotina_bot, (void*)&bots[i]);
            void* retorno_bot;
            pthread_join(threads_bots[i], &retorno_bot);
            pontuacoes_bots[i] = *(int*)retorno_bot;
            free(retorno_bot);
        }

        //Dealer/Casa
        pthread_create(&thread_dealer, NULL, rotina_dealer, (void*)&dealer);
        void* retorno_dealer;
        pthread_join(thread_dealer, &retorno_dealer);
        int pontuacao_dealer = *(int*)retorno_dealer;
        free(retorno_dealer);

        tela_1_pontuacao_final(pontuacao_dealer, pontuacao_jogador);
        tela_2_pontuacao_final(pontuacoes_bots, bots);
        pontuacao_final(pontuacao_dealer, pontuacao_jogador, jogador, valorAposta);

        system("clear");
        tela_dados_jogador(jogador);        
        if (jogador->saldo == 0) {
            printf("\t❌ Seu saldo acabou!\n");
            sleep(4);
            break;
        }

        printf("\n\tDeseja jogar novamente? (s/n): ");
        char opcao[2];
        fgets(opcao, sizeof(opcao), stdin);
        limpar_buffer();

        if (opcao[0] == 'n' || opcao[0] == 'N') {
            break;
        }
    }

    system("clear");
    printf("\n\t----------------------------------------------\n");
    printf("\t                Saindo da mesa...               \n");
    printf("\t-----------------------------------------------\n");
    sleep(3);
}