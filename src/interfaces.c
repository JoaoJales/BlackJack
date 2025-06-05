#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "interfaces.h"

void limpar_buffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

JogadorInfo tela_apresentacao(){
    system("clear");
    printf("\t---------------------------------------\n");
    printf("\t|            BLACK JACK 21             |\n");
    printf("\t---------------------------------------\n");
    printf("\t|             Bem-vindo!               |\n");
    printf("\t---------------------------------------\n\n");

    JogadorInfo jogador = criarJogador();

    return jogador;
}

void tela_Inicial(JogadorInfo jogador){
    system("clear");
    printf("\t----------------------------------------\n");
    printf("\t|            BLACK JACK 21             |\n");
    printf("\t----------------------------------------\n");
    printf("\t| Jogador: %s      | Saldo: R$%2.lf    |\n", jogador.nome, jogador.saldo);
    printf("\t----------------------------------------\n\n");
    printf("\t           MENU:               \n");
    printf("\t           Inicia Jogo:  (1)               \n");
    printf("\t           Multiplayer:  (2)              \n");
    printf("\t           Como Jogar?   (3)                \n");
    printf("\t           Creditos:     (4)                \n");
    printf("\t           Sair do Jogo: (5)              \n\n");
    printf("\t           Escolha uma opcao: ");
}


void tela_como_jogar() {
    system("clear");
    printf("\t-------------------------------------\n");
    printf("\t|           COMO JOGAR              |\n");
    printf("\t-------------------------------------\n\n");
    printf("\t🃏 Bem-vindo ao Blackjack!\n\n");

    printf("\t1- Objetivo:\n");
    printf("\t  - Chegar o mais próximo possível de 21 pontos\n");
    printf("\t  - Sem ultrapassá-los!\n\n");

    printf("\t2- Cartas:\n");
    printf("\t  - Cartas numéricas valem seu próprio valor\n");
    printf("\t  - J, Q e K valem 10 pontos\n");
    printf("\t  - A (Ás) vale 11 pontos (ou 1 se ultrapassar 21)\n\n");

    printf("\t3- Regras básicas:\n");
    printf("\t  - Você começa com 2 cartas\n");
    printf("\t  - O dealer também recebe 2 cartas e deixa uma oculta\n");
    printf("\t  - Você decide se deseja \"comprar mais uma carta\"\n");
    printf("\t  - Se passar de 21, perde automaticamente\n");
    printf("\t  - Depois que você parar, o dealer joga\n\n");

    printf("\t4- Apostas:\n");
    printf("\t  - Você começa com R$100,00 de saldo\n");
    printf("\t  - A aposta mínima é R$5 (múltiplos de 5)\n");
    printf("\t  - Se vencer, recebe o dobro da aposta\n");
    printf("\t  - Em caso de empate, recupera sua aposta\n");
    printf("\t  - Se perder, a casa fica com a aposta\n\n");

    printf("\t5- Como interagir:\n");
    printf("\t  - Digite o valor da aposta quando solicitado\n");
    printf("\t  - Depois, digite 's' para comprar uma nova carta ou 'n' para parar\n\n");

    printf("\t🎯 Boa sorte e divirta-se!\n\n");
    printf("\tPressione enter para voltar ao menu...");
    getchar();
}

void tela_creditos(){
    system("clear");
    printf("\t----------------------------------------------------\n");
    printf("\t|       Projeto final Sistemas Operacionais        |\n");
    printf("\t----------------------------------------------------\n\n");

    printf("\t------------------------------------------------------------------\n");
    printf("\tProjeto final da materia de Sistemas Operacionais\n");
    printf("\tObjetivo: desenvolver um jogo utilizando threads e semaforos\n");
    printf("\tProfessor(a): Beatriz Campos\n");
    printf("\tUniversidade Catolica de Brasilia\n");
    printf("\t------------------------------------------------------------------\n\n");

    printf("\t------------------------------------------------------------------\n");
    printf("\tDesenvolvedores:\n");
    printf("\t- Joao Ricardo Jales Cirino\n");
    printf("\t- Felipe Lima Duarte\n");
    printf("\t- Henrique Vinha Rocha\n");
    printf("\t- Gustavo Domingues de Sousa\n");
    printf("\t------------------------------------------------------------------\n");

    printf("\t🎯 Boa sorte e divirta-se!\n\n");
    printf("\tPressione enter para voltar ao menu...");
    getchar();
}


void tela_dados_jogador(JogadorInfo* jogador){
    printf("\t----------------------------------------\n");
    printf("\t| Jogador: %s      | Saldo: R$%2.lf    |\n", jogador->nome, jogador->saldo);
    printf("\t----------------------------------------\n\n");
}

void tela_1_game(double valorAposta){
        printf("\t----------------------------------------------\n");
        printf("\t|               Aposta: R$%2.lf                 |\n", valorAposta);
        printf("\t----------------------------------------------\n");
        printf("\t----------------------------------------------\n");
        printf("\t|         🃏 Embaralhando cartas...         |\n");
        printf("\t----------------------------------------------\n");
        sleep(1);
}

void tela_empate(JogadorInfo* jogador){
    system("clear");
    printf("\t----------------------------------------------\n");
    printf("\t|                  Empate! 🤝                |\n");
    printf("\t----------------------------------------------\n");
    printf("\t----------------------------------------------\n");
    printf("\t                 Saldo: R$%2.lf              \n", jogador->saldo);
    printf("\t----------------------------------------------\n\n");
    printf("\n");
    printf("\tPressione enter para voltar ao menu...");
    getchar();
}

void tela_jogador_venceu(JogadorInfo* jogador){
    system("clear");
    printf("\t---------------------------------------------\n");
    printf("\t|               Voce venceu! 🏆             |\n");
    printf("\t---------------------------------------------\n");
    printf("\t---------------------------------------------\n");
    printf("\t                Saldo: R$%2.lf               \n", jogador->saldo);
    printf("\t---------------------------------------------\n\n");
    printf("\n");
    printf("\tPressione enter para voltar ao menu...");
    getchar();
}


void tela_casa_venceu(JogadorInfo* jogador){
    system("clear");
    printf("\t----------------------------------------------\n");
    printf("\t|                 Casa venceu! 💀            |\n");
    printf("\t----------------------------------------------\n");
    printf("\t----------------------------------------------\n");
    printf("\t                  Saldo: R$%2.lf             \n", jogador->saldo);
    printf("\t----------------------------------------------\n\n");
    printf("\n");
    printf("\tPressione enter para voltar ao menu...");
    getchar();    
}

void tela_estourou(JogadorInfo* jogador){
    system("clear");
    printf("\t------------------------------------------------\n");
    printf("\t|        💥 Voce estourou 💥 Casa vence.      |\n");
    printf("\t------------------------------------------------\n");
    printf("\t------------------------------------------------\n");
    printf("\t                  Saldo: R$%2.lf              \n", jogador->saldo);
    printf("\t------------------------------------------------\n\n");
    printf("\n");
    printf("\tPressione enter para voltar ao menu...");
    getchar();
}


void tela_1_pontuacao_final(int pont_dealer, int pont_jogador){
    system("clear");
    printf("\n\t----------------------------------------------\n");
    printf("\t            🏁 Pontuação Final:\n");
    sleep(1);
    printf("\t             Casa: %d\n", pont_dealer);
    sleep(1);
    printf("\t             Voce: %d\n", pont_jogador);
    printf("\t------------------------------------------------\n");
    
}

void tela_2_pontuacao_final(int* pont_bots, BotsInfo bots[]){
    for (int i = 0; i < NUM_BOTS; i++)
    {
        printf("\t             %s: %d\n", bots[i].nome, pont_bots[i]);
        sleep(1);
    }
    printf("\t------------------------------------------------\n");
    sleep(5);
    
}