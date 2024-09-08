#include "Tablero.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

void *** tablero; // definicion

int size; // definicion
int limite_turnos; // definicion

coordBarcos coordenadas;
Barco *barcos;
char locaciones;
int vivos;
int numbarcos = 0;
void dificultad(int *r){
    printf("Seleccione la dificultad:\n 1. Facil: 11x11 casillas, 5 barcos\n 2. Medio: 17x17 casillas, 7 barcos\n 3. Dificil: 21x21 casillas, 9 barcos\n");
    printf("Ingrese un numero: ");
    scanf("%d", r);
    if ((*r >=1) && (*r<=3)) {return;
    } else {
        printf("Dificultad no valida, ingresar dificultad nuevamente\n");
        dificultad(r);
    }

}
void inicializarTablero(int r){
    int n, p;
    if (r == 1){n = 11; p =30;}    else if (r == 2){n = 17; p = 25;}   else if (r == 3){n = 21; p =15;} //asigna el valor de de n segun la dificultad elegida
    
    size = n; //clona el tamano del tablero
    limite_turnos = p; //clona la cantidad de turnos
    tablero = (void ***)malloc(n*sizeof(void **)); // hace n punteros a punteros
    for (int i= 0; i<n ; i++){
        tablero[i] = (void **)malloc(n*sizeof(void *)); // hace n punteros a void
        for (int j = 0; j<n; j++){
            tablero[i][j] = (void *)malloc(sizeof(int)); // hace un puntero a void
            int *status = (int *)tablero[i][j];
            *status = 0; //cada casilla comienza sin ser disparada
        }
        
    }
    generaBarcos(r);
    printf("Tablero inicializado\n");
    return;
}
void posicionaBarcos(int x, int y,int direccion, int tamano, coordBarcos coordenadas[]){
    printf("%d %d %d %d\n",x,y,direccion,tamano);
    for (int i=0; i<tamano; i++){
        if (direccion == 0){
            int *status = (int *)tablero[x][y-i]; 
            *status = 4; //modifica el valor del status de la casilla
            barcos[numbarcos].coordenadas[i].x = x; // agrega las coordenadas al sruct Barco
            barcos[numbarcos].coordenadas[i].y = y-i;
        } else if (direccion == 1){
            int *status = (int *)tablero[x][y+i];
            *status = 4;
            barcos[numbarcos].coordenadas[i].x = x;
            barcos[numbarcos].coordenadas[i].y = y+i;
        } else if (direccion == 2){
            int *status = (int *)tablero[x-i][y];
            *status = 4;
            barcos[numbarcos].coordenadas[i].x = x-i;
            barcos[numbarcos].coordenadas[i].y = y;
        } else if (direccion == 3){
            int *status = (int *)tablero[x+i][y];
            *status = 4;
            barcos[numbarcos].coordenadas[i].x = x+i;
            barcos[numbarcos].coordenadas[i].y = y;
        }
    }
    for (int i = 0; i < vivos; i++) {
        for(int j = 0; j <barcos[i].tamano; j++){
            printf("%d %d\n",barcos[i].coordenadas[j].x,barcos[i].coordenadas[j].y);
        }
    }

    return;
}
void creaPosBarcos(coordBarcos coordenadas[], int tamano){;
    srand(time(NULL)); //para generar numeros random
    int flag;
    int x,y,direccion;
    do{
        x = rand() %size +0; 
        y = rand() %size +0; //crea coordenadas iniciales X,Y

        direccion = rand() %4 +0; //0 = arriba, 1 = abajo, 2 = izquierda,3 = derecha
        flag = compruebaBarcos(x,y,direccion,tamano);
    }while(flag !=1);// loopea hasta que un barco pueda ser posicionado de forma segura
    printf("flag\n");
    posicionaBarcos(x,y,direccion,tamano, coordenadas);
    printf("%d kyasdbasdjl\n", numbarcos);
    numbarcos+=1;
    return;
}

void generaBarcos(int r) {
    if (r == 1) { // si esta en facil, crea 2 barcos de 1x2, 1 de 1x3, 1 de 1x4 y 1 de 1x5
        barcos = (Barco *)malloc(5*sizeof(Barco));

        for (int i = 0; i < 5; i++) {
            barcos[i].tamano = (i < 2) ? 2 : (i == 2) ? 3 : (i == 3) ? 4 : 5;
            barcos[i].coordenadas = (coordBarcos *)malloc(barcos[i].tamano * sizeof(coordBarcos));
            if (barcos[i].coordenadas == NULL) {
                perror("Failed to allocate memory for coordenadas");
                exit(EXIT_FAILURE);
            }
            creaPosBarcos(barcos[i].coordenadas, barcos[i].tamano);
        }

        printf("mamaguevazo\n");
        for(int i=0; i<5;i++){
            printf("pinocho\n");
            printf("%d\n",barcos[i].tamano);
            int k = barcos[i].tamano;
            printf("mogusdsa\n");
            for(int j=0; j<k ;j++){
                printf("%d %d\n",barcos[i].coordenadas[j].x,barcos[i].coordenadas[j].y);
            }
        }
    }
    return;
}


void mostrarTablero() {
    for (int i = 0; i < size; i++) {
        printf("|");
        for (int j = 0; j < size; j++) {
            int *status = (int *)tablero[i][j];
            if (*status == 0) { //0 es que no se ha disparado, 1 = X es impacto, 2=O es fallo , 4 es que hay un barco que no ha sido disparado
                printf(" ");
            } else if (*status == 1) {
                printf("X");
            } else if (*status == 2) {
                printf("O");
            } else if (*status == 3) {
                printf("!");
            } else if (*status == 4) {
                printf("?");
            }
            printf("|");
        }
        printf("\n");
    }
}

int compruebaBarcos(int x, int y, int direccion, int tamano){
    int aux = 0;
    if (direccion ==0){
        for (int i = 0; i<tamano; i++){
            if(y-i >= 0){
                int *status = (int *)tablero[x][y-i];
                if (*status == 0) aux += 1;
            } else return 0;
        }
    } else if (direccion == 1){
        for (int i = 0; i<tamano; i++){
            if(y+i < size){
                int *status = (int *)tablero[x][y+i];
                if (*status == 0) aux += 1;
            } else return 0;
        }
    } else if (direccion == 2){
        for (int i = 0; i<tamano; i++){
            if(x-i >= 0){
                int *status = (int *)tablero[x-i][y];
                if (*status == 0)aux += 1;
            } else return 0;
        }
    } else if (direccion == 3){
        for (int i = 0; i<tamano; i++){
            if(x+i < size){
                int *status = (int *)tablero[x+i][y];
                if (*status == 0) aux += 1;
            } else return 0;
        }
    }
    if (aux == tamano) return 1;
    return 0;
}


void limpiabarcos(){
    for (int i = 0; i < 5; i++) {
        free(barcos[i].coordenadas);
    }
    free(barcos);
}