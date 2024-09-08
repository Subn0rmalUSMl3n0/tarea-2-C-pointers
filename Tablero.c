#include "Tablero.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void *** tablero; // definicion

int size; // definicion
int limite_turnos; // definicion

Barco barcos;
char locaciones;

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
void generaBarcos(int r){
    int u;
    if (r == 1){u = 5;}    else if (r == 2){u = 7;}   else if (r == 3){u = 9;} //asigna el valor de de n segun la dificultad elegida
    barcos.vivos = u;
    barcos.casillas = (int **)malloc(u*sizeof(int *));
    for (int i = 0; i<u; i++){
        barcos.casillas[i] = (int *)malloc(2*sizeof(int));
        barcos.casillas[i][0] = rand()%size;
        barcos.casillas[i][1] = rand()%size;
    }
    return;                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                               
}
void mostrarTablero() {
    for (int i = 0; i < size; i++) {
        printf("|");
        for (int j = 0; j < size; j++) {
            int *status = (int *)tablero[i][j];
            if (*status == 0) { //0 es que no se ha disparado, 1 = X es impacto, 2=O es fallo 
                printf(" ");
            } else if (*status == 1) {
                printf("X");
            } else if (*status == 2) {
                printf("O");
            }
            printf("|");
        }
        printf("\n");
    }
}

int compruebaBarcos(int x, int y)