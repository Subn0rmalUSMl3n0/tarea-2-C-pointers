#include "Cartas.h"

#include <stdio.h>
#include <time.h>
#include <stdlib.h>

Mano Cartas;
void inicializarMazo(){
    Cartas.disponibles = 5;
    Cartas.carta = (void **)malloc(5*sizeof(void *));
    for (int i = 0; i<5; i++){
        Cartas.carta[i] = (void *) disparoSimple;

    }
    printf("Mazo inicializado\n");
    return;
};

void mostrarMazo(){
    for (int i = 0; i<5; i++){
        printf("%d. ", i+1);
        if (Cartas.carta[i] == disparoSimple){
            printf("Simple");
        } else if(Cartas.carta[i] == disparoGrande){
            printf("Grande");
        } else if(Cartas.carta[i] == disparoLineal){
            printf("Lineal");
        } else if(Cartas.carta[i] == disparoRadar){
            printf("Radar");
        } else if(Cartas.carta[i] == disparo500KG){
            printf("500KG");
        }
        if (i != 4){printf(" | ");}
    }
    printf("\n");
    return;
};

void * disparoSimple(int x, int y){
    //printf("Disparo simple en %d, %d\n", x, y);
    printf("GUP\n");
    return NULL;
};

void * disparoGrande(int x, int y){
    //printf("Disparo grande en %d, %d\n", x, y);
    printf("BOOM\n");
    return NULL;
};

void * disparoLineal(int x, int y){
    //printf("Disparo lineal en %d, %d\n", x, y);
    printf("PUM\n");
    return NULL;
};

void * disparoRadar(int x, int y){
    //printf("Disparo radar en %d, %d\n", x, y);
    printf("BEEP\n");
    return NULL;
};

void * disparo500KG(int x, int y){
    //printf("Disparo 500KG en %d, %d\n", x, y);
    printf("KYA\n");
    return NULL;
};