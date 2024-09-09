#include "Tablero.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

void *** tablero; // definicion
int size, limite_turnos; // definicion

// define variables tipo struct
coordBarcos coordenadas;
Barco *barcos;

int vivos;
int numbarcos = 0;


// pide la dificultad entre 1 y 3
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

//para inicializar el tablero segun la dificultad
void inicializarTablero(int r){
    int n, p; // n = tamaño del tablero, p = cantidad de turnos
    if (r == 1){n = 11; p =30;}    else if (r == 2){n = 17; p = 25;}   else if (r == 3){n = 21; p =15;} //asigna el valor de de n segun la dificultad elegida
    
    size = n; //clona el tamano del tablero
    limite_turnos = p; //clona la cantidad de turnos
    tablero = (void ***)malloc(n*sizeof(void **)); // crea n punteros a void, para el arreglo de casillas X
    for (int i= 0; i<n ; i++){
        tablero[i] = (void **)malloc(n*sizeof(void *)); // crea n punteros a void, para el arreglo de casillas Y
        for (int j = 0; j<n; j++){
            tablero[i][j] = (void *)malloc(sizeof(int)); // hace un puntero a void, para guardar el estado de la casilla
            int *status = (int *)tablero[i][j];
            *status = 0; //cada casilla comienza sin ser disparada
        }
        
    }
    generaBarcos(r);
    return;
}

//funcion para posicionar los barcos en el tablero segun la direccion y el tamaño
void posicionaBarcos(int x, int y,int direccion, int tamano, coordBarcos coordenadas[]){
    for (int i=0; i<tamano; i++){
        if (direccion == 0){ // 0 = izquierda, 1 = derecha, 2 = arriba, 3 = abajo
            int *status = (int *)tablero[x][y-i]; 
            *status = 4; //modifica el status de la casilla a 'hay un barco sin disparar'
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
    return;
}

//crea las posiciones del barco,de forma que se puedan enviar a posicionaBarcos sin que el barco salga del mapa ni se superpongan
void creaCoordenadasBarcos(coordBarcos coordenadas[], int tamano){;
    srand(time(NULL)); //para generar numeros random
    int flag;
    int x,y,direccion;
    do{
        x = rand() %size +0; 
        y = rand() %size +0; //crea coordenadas iniciales X,Y

        direccion = rand() %4 +0; //0 = izquierda, 1 = derecha, 2 = arriba, 3 = abajo
        flag = verificaPosicionBarcos(x,y,direccion,tamano);
    }while(flag !=1);// loopea hasta que un barco pueda ser posicionado de forma segura

    posicionaBarcos(x,y,direccion,tamano, coordenadas); //llama a la funcion para colocar el barco

    numbarcos+=1; //suma uno a la cantidad de barcos
    return;
}

void generaBarcos(int r) {
    if (r == 1) { // si esta en facil, crea:
        barcos = (Barco *)malloc(5*sizeof(Barco));
        barcos[0].tamano =2;
        barcos[1].tamano =2;// 2 de 1x2
        barcos[2].tamano =3;//1 de 1x3
        barcos[3].tamano =4;//1 de 1x4
        barcos[4].tamano =5;//1 de 1x5
        for (int i = 0; i < 5; i++) {
            barcos[i].coordenadas = (coordBarcos *)malloc(barcos[i].tamano * sizeof(coordBarcos)); // a cada barco[i], le asigna memoria
            barcos[i].casillas_hundidas = 0; 
            barcos[i].vivoflag = 1; //cada barco comienza con 0 casillas hundidas y con el estado vivo
            creaCoordenadasBarcos(barcos[i].coordenadas, barcos[i].tamano); //crea las posiciones de cada barco
        }
    } else if(r ==2){// dificultad media, crea:
        barcos = (Barco *)malloc(7*sizeof(Barco));
        barcos[0].tamano =2; //3 de 1x2
        barcos[1].tamano =2;
        barcos[2].tamano =2;
        barcos[3].tamano =3; //2 de 1x3
        barcos[4].tamano =3;
        barcos[5].tamano =4; //1 de 1x4
        barcos[6].tamano =5; //1 de 1x5
        for (int i = 0; i < 7; i++) {
            barcos[i].coordenadas = (coordBarcos *)malloc(barcos[i].tamano * sizeof(coordBarcos)); // a cada barco le asigna memoria segun el tamaño
            barcos[i].casillas_hundidas = 0;
            barcos[i].vivoflag = 1; //cada barco comienza con 0 casillas hundidas y con el estado vivo
            creaCoordenadasBarcos(barcos[i].coordenadas, barcos[i].tamano); //crea las posiciones de cada barco
        } 
    } else if(r ==3){// si esta en dificl, crea:
        barcos = (Barco *)malloc(9*sizeof(Barco));
        barcos[0].tamano =2; //3 de 1x2
        barcos[1].tamano =2;
        barcos[2].tamano =2;
        barcos[3].tamano =3; //2 de 1x3
        barcos[4].tamano =3;
        barcos[5].tamano =4; //2 de 1x4
        barcos[6].tamano =4;
        barcos[7].tamano =5; //2 de 1x5
        barcos[8].tamano =5;
        for (int i = 0; i < 9; i++) {
            barcos[i].coordenadas = (coordBarcos *)malloc(barcos[i].tamano * sizeof(coordBarcos)); // a cada barco le asigna memoria segun el tamaño
            barcos[i].casillas_hundidas = 0;
            barcos[i].vivoflag = 1; //cada barco comienza con 0 casillas hundidas y con el estado vivo
            creaCoordenadasBarcos(barcos[i].coordenadas, barcos[i].tamano); //crea las posiciones de cada barco
        }
    }
    return;
}


//comprueba si un barco puede ser posicionado en una casilla, segun direccion y tamaño
int verificaPosicionBarcos(int x, int y, int direccion, int tamano){
    int aux = 0;
    if (direccion ==0){// si va para la izquierda, revisa que todas las casillas que vaya a usar el barco esten dentro del tablero y libres
        for (int i = 0; i<tamano; i++){
            if(y-i >= 0){
                int *status = (int *)tablero[x][y-i];
                if (*status == 0) aux += 1; // si la casilla esta disponible suma 1
            } else return 0;
        }

    } else if (direccion == 1){ // revisa las casillas hacia la derecha
        for (int i = 0; i<tamano; i++){
            if(y+i < size){
                int *status = (int *)tablero[x][y+i];
                if (*status == 0) aux += 1;
            } else return 0;
        }

    } else if (direccion == 2){ // revisa las casillas hacia arriba
        for (int i = 0; i<tamano; i++){
            if(x-i >= 0){
                int *status = (int *)tablero[x-i][y];
                if (*status == 0)aux += 1;
            } else return 0;
        }

    } else if (direccion == 3){ // revisa las casillas hacia abajo
        for (int i = 0; i<tamano; i++){
            if(x+i < size){
                int *status = (int *)tablero[x+i][y];
                if (*status == 0) aux += 1;
            } else return 0;
        }
    }

    //, si el numero de casillas disponibles es igual al tamaño del barco, la direccion es valida
    if (aux == tamano) return 1; //1 es que se puede posicionar sin problemas
    return 0; //0 es que no se puede posicionar
}


// para mostrar el tablero por la terminal
void mostrarTablero() {
    for (int i = 0; i < size; i++) { // por cada xi
        printf("|");
        for (int j = 0; j < size; j++) {// por cada xi,yj
            int *status = (int *)tablero[i][j];
            if (*status == 0) { // no se ha disparado y no hay barco
                printf(" ");
            } else if (*status == 1) { // impacto
                printf("X");
            } else if (*status == 2) { // fallo
                printf("O");
            } else if (*status == 3) { // el radar encotro un barco
                printf("!");
            } else if (*status == 4) { // hay un barco, pero no ha sido disparado ni revelado
                printf(" ");
            } else if (*status == 5) { // el radar no encontro nada
                printf("-");
            }
            printf("|");
        }
        printf("\n");
    }
}

void mostrarTableroFinal(){
    for (int i = 0; i < size; i++) { // por cada xi
        printf("|");
        for (int j = 0; j < size; j++) {// por cada xi,yj
            int *status = (int *)tablero[i][j];
            if (*status == 0) { // no se ha disparado y no hay barco
                printf(" ");
            } else if (*status == 1) { // impacto
                printf("X");
            } else if (*status == 2) { // fallo
                printf("O");
            } else if (*status == 3) { // el radar encotro un barco
                printf("!");
            } else if (*status == 4) { // hay un barco, pero no ha sido disparado ni revelado
                printf("!");
            } else if (*status == 5) { // el radar no encontro nada
                printf("-");
            }
            printf("|");
        }
        printf("\n");
    }
}
// libera la memoria de los structs barco y tablero
void limpiabarcos(){
    for (int i = 0; i < 5; i++) {
        free(barcos[i].coordenadas); // libera cada arreglo de coordenadas de cada barco
    }
    free(barcos); // libera cada barco
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            free(tablero[i][j]); // libera cada estatus de cada casilla
        }
        free(tablero[i]); // libera cada casilla y
    }
    free(tablero); //libera cada casilla x
}