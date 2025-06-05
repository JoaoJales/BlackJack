#ifndef DEALER_H
#define DEALER_H

#define MAX_CARTAS 12

typedef struct {
    int cartas[MAX_CARTAS];
    int num_cartas;
} DealerInfo;

void* rotina_dealer(void* arg);

#endif