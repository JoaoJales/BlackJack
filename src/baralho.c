#include <stdio.h>
#include <stdlib.h>
#include <time.h> // funções relacionadas a tempo (usado para o srand)
#include <semaphore.h> //semáforos (controle de concorrência).
#include "baralho.h"

//Declarações globais (estão visíveis apenas neste arquivo por serem "static"):
static int baralho[TAM_BARALHO];
static int topo = 0;

// semáforo para controlar o acesso ao baralho:
sem_t sem_baralho;

void inicializar_baralho() {
    srand(time(NULL)); // inicializa o gerador de números aleatórios com base no tempo atual para embaralhar diferente a cada execução.

    for (int i = 0; i < TAM_BARALHO; i++) {
        baralho[i] = (i % 13) + 1; // cartas de 1 a 13
    }

    embaralhar();
    embaralhar();
    embaralhar();

    sem_init(&sem_baralho, 0, 1); // 1 thread por vez // semáforo binário// Mutex
}

void embaralhar() {
    for (int i = 0; i < TAM_BARALHO; i++) {
        int j = rand() % TAM_BARALHO;

        int aux = baralho[i];
        baralho[i] = baralho[j];
        baralho[j] = aux;
    }
    topo = 0;
}

int comprar_carta() {
    sem_wait(&sem_baralho); //tenta entrar na seção crítica

    if (topo >= TAM_BARALHO) {
        embaralhar();
    }

    int carta = baralho[topo];
    topo++;
    sem_post(&sem_baralho); //Libera o semáforo 

    return carta;
}