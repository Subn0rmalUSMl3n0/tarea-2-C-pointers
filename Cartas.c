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
    srand(time(NULL));
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
    preparacionesDisparo(x, y, 1);
    int NextShot = rand() % 100;
    if (NextShot <= 65){
        return *disparoSimple;
    } else if (NextShot <= 85){
        return *disparoGrande;
    } else if (NextShot <= 90){
        return disparoLineal;
    } else{
        return disparoRadar;
    };
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

void preparacionesDisparo(int x, int y, int tipo){
    if (tipo ==1){//disparo simple
        procesarDisparo(x, y, coordenadas);
    } else if(tipo ==2){//disparo grande
        procesarDisparo(x,y,coordenadas); //procesa el centro
    }
};

void procesarDisparo(int x, int y, coordBarcos coordenadas){
    int *status = (int *)tablero[x][y];
    if (*status == 4){
        *status = 1;
        printf("Impacto!\n");
    } else if (*status == 0){
        *status = 2;
        printf("Fallo!\n");
    } else if (*status == 1){
        printf("Ya se disparo aca!\n");
    } else if (*status == 2){
        printf("Ya se disparo aca!\n");
    }
    return;

}