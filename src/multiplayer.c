#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <string.h>
#include "multiplayer.h"
#include "jogo.h"
#include "baralho.h"
#include "utils.h"
#include "interfaces.h"

int numJogadores = 0;

void resultado_partida(JogadorInfo* jogagores){
    system("clear");
    printf("\n\t=========== FIM DO JOGO ===========\n");
    printf("\tSaldos finais:\n");
    for (int i = 0; i < numJogadores; i++) {
        printf("\n\t┌────────────────────────────────────┐\n");
        printf("\t│ %s            | Saldo: R$%.2f \n", jogagores[i].nome, jogagores[i].saldo);
        printf("\t└────────────────────────────────────┘\n");
    }

    double maiorSaldo = -1;
    int vencedor;
    for (int i = 0; i < numJogadores; i++) {
        if (jogagores[i].saldo > maiorSaldo) {
            maiorSaldo = jogagores[i].saldo;
            vencedor = i;
        }
    }

    if (maiorSaldo == -1)
    {
        printf("\t---------------------------------\n");
        printf("\t\nTodos os jogadores perderam!\n");
        printf("\t---------------------------------\n");
    }else{
        printf("\t----------------------------------------\n");
        printf("\n\t🏆 %s eh o vencedor com R$%.2f! 🏆\n",jogagores[vencedor].nome, jogagores[vencedor].saldo);
        printf("\t----------------------------------------\n");
    }

    printf("\n\tPressione Enter para voltar ao menu...");
    getchar();
}

void resultados_rodada(int pontos_dealer, JogadorInfo* jogadores, double* valoresApostas, int *numJogadoresAtivos){
    system("clear");
    printf("\n\t============ RESULTADOS ============\n");
    printf("\tCasa: %d pontos\n", pontos_dealer);
    printf("\t------------------------------------\n");

    for (int i = 0; i < numJogadores; i++)
    {
        if(!jogadores[i].ativo) continue;

        int pontos_jogador = calcular_pontuacao(jogadores[i].cartas, jogadores[i].num_cartas);

        printf("\n\t┌────────────────────────────────────┐\n");
        printf("\t│ %s                \n", jogadores[i].nome);
        printf("\t│ Pontos: %-3d                        \n", pontos_jogador);

        if (pontos_jogador > 21)
        {
            printf("\t│ ESTOUROU! Perdeu -R$%.2f          \n", valoresApostas[i]);

        } else if (pontos_dealer > 21 || pontos_jogador > pontos_dealer) {
            double lucro = valoresApostas[i] * 2;
            jogadores[i].saldo += lucro;
            printf("\t│ GANHOU! +R$%.2f                  \n", lucro);

        } else if (pontos_jogador == pontos_dealer) {
            jogadores[i].saldo += valoresApostas[i];
            printf("\t│ EMPATE! Recuperou R$%.2f         \n", valoresApostas[i]);

        } else {
            printf("\t│ PERDEU! -R$%.2f                  \n", valoresApostas[i]);
        }

        printf("\t│ Saldo atual: R$%.2f             \n", jogadores[i].saldo);
        printf("\t└────────────────────────────────────┘\n");

        if (jogadores[i].saldo <= 0 && jogadores[i].ativo)
        {
            printf("\n\t┌────────────────────────────────────┐\n");
            printf("\t    ❌ %s foi eliminado do jogo!\n", jogadores[i].nome);
            printf("\t└────────────────────────────────────┘\n");
            *numJogadoresAtivos -= 1;
            jogadores[i].ativo = 0;
        }

        
        
    }
    
}

void tela_mesa(JogadorInfo* jogadores, DealerInfo* dealer, int numJogadores, int esconderCartaDealer, double* valoresApostas, int numRodadas, int rodadaAtual){
    system("clear");
    printf("\n\t============ BLACKJACK MULTIPLAYER ============\n");
    printf("\t================= RODADA %d/%d =================\n", rodadaAtual, numRodadas);
    sleep(1);
    
    printf("\n\t┌────────────────────────────────────┐\n");
    printf("\t│ 🃏 Cartas casa:                      \n");
    printf("\t");
    imprimir_cartas(dealer->cartas, dealer->num_cartas, esconderCartaDealer);
    printf("\t└────────────────────────────────────┘\n");

    for (int i = 0; i < numJogadores; i++)
    {
        if (!jogadores[i].ativo) continue;
        

        printf("\n\t┌────────────────────────────────────┐\n");
        printf("\t│ 👤 %s            \n", jogadores[i].nome);
        printf("\t│ Saldo: R$%.2f \n", jogadores[i].saldo);
        printf("\t| Aposta: R$%.2f \n\n", valoresApostas[i]);
        printf("\t");
        imprimir_cartas(jogadores[i].cartas, jogadores[i].num_cartas, 0);
        printf("\t└────────────────────────────────────┘\n");
    }
    printf("\n\t================================================\n");
}

void distribuicao_cartas_iniciais_jogadores_multiplayer(JogadorInfo* jogadores){
    for (int i = 0; i < numJogadores; i++)
    {
        if (!jogadores[i].ativo) continue;
        
        jogadores[i].cartas[0] = comprar_carta();
        jogadores[i].cartas[1] = comprar_carta();
        jogadores[i].num_cartas = 2;
    }
}

void distribuicao_cartas_iniciais_dealer_multiplayer(DealerInfo* dealer){
    dealer->cartas[0] = comprar_carta();
    dealer->cartas[1] = comprar_carta();
    dealer->num_cartas = 2;
}

void apostas(JogadorInfo* jogadores, double* valoresApostas){
    for (int i = 0; i < numJogadores; i++)
    {
        if (jogadores[i].saldo <= 0)
        {
            valoresApostas[i] = 0.0;
            continue;
        }
        
        valoresApostas[i] = aposta(&jogadores[i]);
    }
}

void cadastrar_jogadores(JogadorInfo* jogadores){
    for (int i = 0; i < numJogadores; i++)
    {
        system("clear");
        printf("\n\t=========== JOGADOR %d ===========\n", i + 1);
        printf("\tNome: ");
        fgets(jogadores[i].nome, 50, stdin);
        jogadores[i].nome[strcspn(jogadores[i].nome, "\n")] = '\0';
        jogadores[i].num_cartas = 0;
        jogadores[i].saldo = 100.0;
        jogadores[i].ativo = 1;
    }
    
}

void multiplayer(){
    system("clear");
    printf("\n\t=========== MODO MULTIPLAYER ===========\n");
    int numRodadas;
    int numJogadoresAtivos;

    while (1)
    {
        printf("\n\tQuantos jogadores (1-%d)? ", MAX_JOGADORES);
        scanf("%d", &numJogadores);
        limpar_buffer();
        
        if (numJogadores >= 2 && numJogadores <= MAX_JOGADORES)
        {
            break;
        }

        printf("\t\n Numero de Jogadores invalido!\n");
    }
    numJogadoresAtivos = numJogadores;

    while (1)
    {
        printf("\n\tQuantas rodadas (1-%d)? ", MAX_RODADAS);
        scanf("%d", &numRodadas);
        limpar_buffer();  
        
        if (numJogadores >= 1 && numJogadores <= 10)
        {
            break;
        }
        
        printf("\t\n Numero de Rodadas invalido!\n");
    }

    DealerInfo dealer;
    JogadorInfo jogadores[numJogadores];

    cadastrar_jogadores(jogadores);
    
    pthread_t threads_jogadores[numJogadores], thread_dealer;

    double valoresApostas[numJogadores];
    for (int i = 0; i < numRodadas; i++)
    {
        if(numJogadoresAtivos == 1) break;
        system("clear");
        printf("\n\n\t================= RODADA %d/%d =================\n", i+1, numRodadas);
        sleep(3);
        apostas(jogadores, valoresApostas);

        inicializar_baralho();
        
        distribuicao_cartas_iniciais_dealer_multiplayer(&dealer);
        distribuicao_cartas_iniciais_jogadores_multiplayer(jogadores);

        for (int  j = 0; j < numJogadores; j++)
        {
            if (!jogadores[j].ativo) continue;
            
            tela_mesa(jogadores, &dealer, numJogadores, 1, valoresApostas, numRodadas, i+1);
            printf("\t                 Vez de %s\n", jogadores[j].nome);
            printf("\t================================================\n");
            pthread_create(&threads_jogadores[j], NULL, rotina_jogador, (void*)&jogadores[j]);
            void* retorno_jogador;
            pthread_join(threads_jogadores[j], &retorno_jogador);
            free(retorno_jogador);
        }

        pthread_create(&thread_dealer, NULL, rotina_dealer, (void*)&dealer);
        void* retorno_dealer;
        pthread_join(thread_dealer, &retorno_dealer);
        int pontuacao_dealer = *(int*)retorno_dealer;
        free(retorno_dealer);

        resultados_rodada(pontuacao_dealer, jogadores, valoresApostas, &numJogadoresAtivos);
        printf("\n\tPressione Enter para continuar...");
        getchar();
    }

    resultado_partida(jogadores);
    
}
