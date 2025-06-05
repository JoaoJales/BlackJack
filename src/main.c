#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "jogador.h"
#include "interfaces.h"
#include "jogo.h"



int main() {
    int opcao;
    JogadorInfo jogador;
    jogador = tela_apresentacao();
    do{
        tela_Inicial(jogador);
        scanf("%d", &opcao);
        limpar_buffer();

        if (jogador.saldo <= 0)
        {
            printf("\n\t----------------------------------------------\n");
            printf("\t|             Saldo insuficiente!  ❌         |\n");
            printf("\t------------------------------------------------\n");
            opcao = 0;
        }
        

        switch (opcao){
        case 1:
            game(&jogador);
            break;
        case 2:
            // estatisticas();
            break;
        case 3:
            tela_como_jogar();
            break;
        case 4:
            tela_creditos();
            break;
        case 5:
            opcao = 0;
            break;
        default:
            printf("Escolha invalida!\n");
            break;
        }
        
    } while (opcao);

    system("clear");
    printf("\n\t--------------------------------------------\n");
    printf("\t|            Obrigado por Jogar! 🎮         |\n");
    printf("\t---------------------------------------------\n");

    return 0;
}
