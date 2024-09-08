#include "Cartas.h"

#include <stdio.h>
#include <time.h>
#include <stdlib.h>

Mano Cartas;
void inicializarMazo(){
    Cartas.disponibles = 5;
    Cartas.carta = (void **)malloc(5*sizeof(void *));
    for (int i = 0; i<5; i++){
        Cartas.carta[i] = (void *) disparo500KG;

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
        } else if(Cartas.carta[i] == brokenCannon){
            printf("Cañon Roto");
        }
        if (i != 4){printf(" | ");}
    }
    printf("\n");
    return;
};

void * disparoSimple(int x, int y){
    preparacionesDisparo(x, y, 1);
    int NextShot = rand() % 101 +1;
    if (NextShot <= 65){
        return disparoSimple;
    } else if (NextShot <= 85){
        return disparoGrande;
    } else if (NextShot <= 90){
        return disparoLineal;
    } else{
        return disparoRadar;
    };
};

void * disparoGrande(int x, int y){
    preparacionesDisparo(x, y, 2);
    int NextShot = rand() % 101 +1;
    if (NextShot <= 80){
        return disparoSimple;
    } else if (NextShot <= 83){
        return disparoGrande;
    } else if (NextShot <= 93){
        return disparoLineal;
    }else if (NextShot <= 98){
        return disparoRadar;
    } else{
        return disparo500KG;
    };
};

void * disparoLineal(int x, int y){
    preparacionesDisparo(x, y, 3);
    int NextShot = rand() % 101 +1;
    if (NextShot <= 85){
        return disparoSimple;
    } else if (NextShot <= 90){
        return disparoGrande;
    } else if (NextShot <= 92){
        return disparoLineal;
    }else if (NextShot <= 98){
        return disparoRadar;
    } else{
        return disparo500KG;
    };
};

void * disparoRadar(int x, int y){
    preparacionesDisparo(x, y, 4);
    int NextShot = rand() % 101 +1;
    if (NextShot <= 75){
        return disparoSimple;
    } else if (NextShot <= 90){
        return disparoGrande;
    } else if (NextShot <= 95){
        return disparoLineal;
    }else if (NextShot <= 97){
        return disparoRadar;
    } else{
        return disparo500KG;
    };
};

void * disparo500KG(int x, int y){
    preparacionesDisparo(x, y, 5);
    Cartas.disponibles -=1;
    return brokenCannon;
};

void * brokenCannon(int x, int y){
    printf("El cañon esta roto, no se puede disparar\n");
    return brokenCannon;
};
void preparacionesDisparo(int x, int y, int tipo){
    if (tipo ==1){//disparo simple
        procesarDisparo(x, y, 0);
    } else if(tipo ==2){//disparo grande
        procesarDisparo(x,y, 1); //procesa el centro
        for (int i = -1; i <= 1; i++) { // Itera desde -1 hasta 1 para centrar en x
            for (int j = -1; j <= 1; j++) { // Itera desde -1 hasta 1 para centrar en y
                if (x + i >= 0 && x + i < size && y + j >= 0 && y + j < size) {
                    if (i == 0 && j == 0) continue; // se salta la casilla central
                    procesarDisparo(x + i, y + j, 2);
                }
            }
        }
    } else if (tipo == 3){//disparo lineal
        int direccion;
        do{
            printf("Seleccione direccion del disparo lineal:\n1. Horizontal\n2. Vertical\n");
            scanf("%d", &direccion);
        }while (direccion != 1 && direccion != 2);
        procesarDisparo(x, y, 1);
        if (direccion == 1){ //horizontal
            for (int i = -2; i <= 2; i++) {
                if (x + i >= 0 && x + i < size) {
                    if (i == 0) continue; //se salta la casilla central
                    procesarDisparo(x + i, y, 2);
                }
            }
        } else if (direccion == 2){ //vertical
            for (int j = -2; j <= 2; j++) {
                if (y + j >= 0 && y + j < size) {
                    if (j == 0) continue; // se salta la casilla central
                    procesarDisparo(x, y + j, 2);
                }
            }
        }
    } else if (tipo == 4){ // disparo radar
        for (int i = -2; i <= 2; i++) {
            for (int j = -2; j <= 2; j++) {
                if (x + i >= 0 && x + i < size && y + j >= 0 && y + j < size) {
                    procesarRadar(x + i, y + j);
                }
            }
        }
    } else if (tipo == 5){ //disparo 500KG
        procesarDisparo(x, y, 1);
        for (int i = -5; i <= 5; i++) {
            for (int j = -5; j <= 5; j++) {
                if (x + i >= 0 && x + i < size && y + j >= 0 && y + j < size) {
                    if (i == 0 && j == 0) continue; // se salta la casilla central
                    procesarDisparo(x + i, y + j, 2); // Procesa las 11x11 casillas alrededor de la central
                }
            }
        
        }
    }
        
};

void procesarDisparo(int x, int y, int flag){
    int *status = (int *)tablero[x][y];
    if (*status == 4){ // si habia un barco que no ha sido disparado
        *status = 1; // el estatus cambia a disparado
        printf("Impacto!\n");
        procesarBarcosEliminados(x,y);
    } else if (*status == 0){
        *status = 2;
        printf("Fallo!\n");
    } else if ((*status == 1 ||*status ==2) && flag ==0){ //si ya se disparo en la casilla, y es disparo simple
        printf("Ya se disparo en esta casilla, ingrese coordenadas nuevamente\n");
        int i, j;
        do{
            printf("Selecciona Coordenadas:\nX:");
            scanf("%d", &i);
            printf("Y:");
            scanf("%d", &j);
            if (i-1>= size || j-1>=size) printf("Coordenadas fuera de rango, por favor intente de nuevo\n");
        }while (i-1>=size || j-1>=size);
        procesarDisparo(i-1, j-1, 0);
    } else if ((*status == 1 ||*status ==2) && flag ==1){ // si ya se disparo en la casilla, pero se quiere usar cualquier otro disparo y esta casilla es la central
        //https://encrypted-tbn0.gstatic.com/images?q=tbn:ANd9GcTkZrHAIXhsa3L7eLZlp27C8bhrBd3TmcTxfA&s

    } else if ((*status == 1 ||*status ==2) && flag ==2){ //si ya se habia disparado en la casilla, pero esto es la onda expansiva del disparo
        //https://encrypted-tbn0.gstatic.com/images?q=tbn:ANd9GcTkZrHAIXhsa3L7eLZlp27C8bhrBd3TmcTxfA&s
    }
}
void procesarRadar(int x, int y){
    int *status = (int *)tablero[x][y];
    if (*status == 4){
        *status = 3; // si hay un barco, el estado pasa a descubierto
    } else if(*status == 0){
        *status = 5; // si no hay barco, el estado pasa a no hay barco
    }// como al disparo radar no le interesa si la casilla actual fue disparada o no, hasta aca
}


//DEBO ELIMINAR
void procesarBarcosEliminados(int x,int y){
    for(int i=0; i<5;i++){
        int k = barcos[i].tamano;
        for(int j=0; j<k ;j++){ // este for se encarga de anular las coordenadas de esta casilla
            if(barcos[i].coordenadas[j].x == x && barcos[i].coordenadas[j].y == y){
                barcos[i].coordenadas[j].x = -1;
                barcos[i].coordenadas[j].y = -1;
            }
        }
        int contador = 0;
        for(int j=0; j<k;j++){// este for se encarga de verificar si el barco fue hundido
            if(barcos[i].coordenadas[j].x == -1 && barcos[i].coordenadas[j].y == -1){
                contador += 1;
            } else break; // a la primera casilla de barco no hundido ,se sale del for
        }
        if (contador == k){// si todas las casillas del barco fueron disparadas
            printf("Barco Hundido!\n");
            vivos -=1;
            printf("Barcos restantes: %d\n", vivos);
        }
    }
}