#include <stdio.h>
#include "utils.h"

int calcular_pontuacao(int* cartas, int num_cartas) {
    int soma = 0;
    int ases = 0;

    for (int i = 0; i < num_cartas; i++) {
        int valor = cartas[i];

        // Valete, Dama, Rei valem 10
        if (valor >= 11 && valor <= 13) {
            soma += 10;
        } else if (valor == 1) {
            soma += 11; // Ace inicialmente vale 11
            ases++;
        } else {
            soma += valor;
        }
    }

    // Se estourou e tem Ás, reduz o valor do Ás para 1
    while (soma > 21 && ases > 0) {
        soma -= 10;
        ases--;
    }

    return soma;
}

void imprimir_cartas(const char* nome, int* cartas, int num_cartas, int esconder_primeira) {
    printf("\t        %s: ", nome);
    for (int i = 0; i < num_cartas; i++) {
        if (i == 0 && esconder_primeira) {
            printf("[??] ");
        } else {
            switch (cartas[i]) {
                case 1: printf("[A] "); break;
                case 11: printf("[J] "); break;
                case 12: printf("[Q] "); break;
                case 13: printf("[K] "); break;
                default: printf("[%d] ", cartas[i]);
            }
        }
    }
    if (esconder_primeira) {

    int carta_sozinha[1];
    carta_sozinha[0] = cartas[1]; 
    printf(" |  Total: %d\n", calcular_pontuacao(carta_sozinha, 1));

    }else{

    printf(" |  Total: %d\n", calcular_pontuacao(cartas, num_cartas));
    }
    
}

void imprimir_uma_carta(int carta){
    switch (carta) {
        case 1: printf("[A] \n"); break;
        case 11: printf("[J] \n"); break;
        case 12: printf("[Q] \n"); break;
        case 13: printf("[K] \n"); break;
        default: printf("[%d] \n", carta);
    }
     
    
}