#include "Cartas.h"

#include <stdio.h>
#include <time.h>
#include <stdlib.h>

Mano Cartas;
int flag500kg =1;
void inicializarMazo(){
    Cartas.disponibles = 5;
    Cartas.carta = (void **)malloc(5*sizeof(void *)); // asigna memoria para las 5 cartas
    for (int i = 0; i<5; i++){
        Cartas.carta[i] = (void *) disparoSimple; //cada carta comienza como disparo simple
    }
    srand(time(NULL)); // para generar numeros random en futuras funciones
    return;
};

//printea por pantalla el mazo disponible
void mostrarMazo(){
    for (int i = 0; i< Cartas.disponibles; i++){
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

void usarCarta(){
    //pregunta por la carta a usar hasta que sea valida
    do{
        printf("Seleccione una carta: ");
        scanf("%d", &selected);
        if (selected < 1 || selected > Cartas.disponibles) printf("Carta no valida, por favor intente de nuevo\n");
    }while(selected < 1 || selected > Cartas.disponibles);

    // pregunta por las coordenadas a disparar hasta que sean validas
    do{
        printf("Selecciona Coordenadas:\nX:");
        scanf("%d", &x);
        printf("Y:");
        scanf("%d", &y);
        if (x> size || y>size) printf("Coordenadas fuera de rango, por favor intente de nuevo\n");
    }while (x>size || y>size || x<1 || y<1);
    // como se preguntan indices del 1 al 5 y de 1 a n, se resta 1 a las variables selected, x, y para aplicar la logica de los for
    void * (*puntero_disparos)(int, int) = Cartas.carta[selected-1]; //crea variable que apuntara al disparo elegido
    Cartas.carta[selected-1] = (void *) (*puntero_disparos)(x-1,y-1); //invoca funcion de carta elegita 
    
    //revisa si algun barco fue eliminado
    procesarBarcosEliminados();
}
//funciones de disparo iniciales, cada disparo llama a la funcion preparacionesDisparo segun su tipo, y se asigna el siguiente disparo segun un numero random del 1 al 100
void * disparoSimple(int x, int y){
    preparacionesDisparo(x, y, 1);
    int NextShot = rand() % 101 +1; // si es 101 +1, los porcentajes van de 1 a 100, no de 0 a 99
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
        if(flag500kg == 1){ //si aun no se utiliza el disparo de 500kg, se llama a la funcion
            return disparo500KG;
        } else {
            return disparoSimple; // si no, manda un disparo simple
        }
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
        if(flag500kg == 1){
            return disparo500KG;  //si aun no se utiliza el disparo de 500kg, se llama a la funcion
        } else {
            return disparoSimple; // si no, manda un disparo simple
        }
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
        if(flag500kg == 1){
            return disparo500KG; //si aun no se utiliza el disparo de 500kg, se llama a la funcion
        } else {
            return disparoSimple; // si no, manda un disparo simple
        }
    };
};

void * disparo500KG(int x, int y){
    preparacionesDisparo(x, y, 5);
    void * (*aux)(int,int); //se crea un puntero auxiliar para guardar la carta que se va a cambiar
    flag500kg -=1; //se cambia el flag para que no se pueda usar de nuevo
    if(selected-1 != 4){ // si la carta de 500kg no es la ultima
        aux = Cartas.carta[4]; 
        Cartas.carta[selected-1] = Cartas.carta[4];
        // la ultima carta swapea con la de 500kg
    } else{
        aux = Cartas.carta[3]; //si la de 500kg es la ultima, aux guarda la penultima
    }
    Cartas.carta[4] = NULL; //la carta de 500kg se deja en un puntero nulo
    Cartas.disponibles -=1; // el mazo pierde una carta para siempre
    return aux;
};


void preparacionesDisparo(int x, int y, int tipo){
    if (tipo ==1){//disparo simple
        Disparo(x, y, 0);
    } else if(tipo ==2){//disparo grande
        Disparo(x,y, 1); //procesa el centro
        for (int i = -1; i <= 1; i++) { // Itera desde -1 hasta 1 para centrar en x
            for (int j = -1; j <= 1; j++) { // Itera desde -1 hasta 1 para centrar en y
                if (x + i >= 0 && x + i < size && y + j >= 0 && y + j < size) { // si la casilla a procesar esta dentro del tablero
                    if (i == 0 && j == 0) continue; // se salta la casilla central
                    Disparo(x + i, y + j, 2);
                }
            }
        }
    } else if (tipo == 3){//disparo lineal
        int direccion;
        do{
            printf("Seleccione direccion del disparo lineal:\n1. Horizontal\n2. Vertical\n");
            scanf("%d", &direccion);
        }while (direccion != 1 && direccion != 2);
        Disparo(x, y, 1);
        if (direccion == 2){ //vertical
            for (int i = -2; i <= 2; i++) {
                if (x + i >= 0 && x + i < size) { // si la casilla a procesar esta dentro del tablero
                    if (i == 0) continue; //se salta la casilla central
                    Disparo(x + i, y, 2);
                }
            }
        } else if (direccion == 1){ //horizontal
            for (int j = -2; j <= 2; j++) {
                if (y + j >= 0 && y + j < size) { // si la casilla a procesar esta dentro del tablero
                    if (j == 0) continue; // se salta la casilla central
                    Disparo(x, y + j, 2);
                }
            }
        }
    } else if (tipo == 4){ // disparo radar
        for (int i = -2; i <= 2; i++) {
            for (int j = -2; j <= 2; j++) {
                if (x + i >= 0 && x + i < size && y + j >= 0 && y + j < size) { // si la casilla a procesar esta dentro del tablero
                    procesarRadar(x + i, y + j);
                }
            }
        }
    } else if (tipo == 5){ //disparo 500KG
        Disparo(x, y, 1);
        for (int i = -5; i <= 5; i++) {
            for (int j = -5; j <= 5; j++) {
                if (x + i >= 0 && x + i < size && y + j >= 0 && y + j < size) { // si la casilla a procesar esta dentro del tablero
                    if (i == 0 && j == 0) continue; // se salta la casilla central
                    Disparo(x + i, y + j, 2); // Procesa las 11x11 casillas alrededor de la central
                }
            }
        
        }
    }
        
};

//cambia el estado de la casilla segun el estado actual y un flag
void Disparo(int x, int y, int flag){
    int *status = (int *)tablero[x][y]; //agarra el estado de la casilla actual
    if (*status == 4 || *status == 3){ // si habia un barco que no ha sido disparado
        *status = 1; // el estatus cambia a disparado
        ProcesarCasillasAfectadas(x,y);
    } else if (*status == 0 || *status == 5){
        *status = 2; // el estatus cambia a disparo errado
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
        Disparo(i-1, j-1, 0);
    } else if ((*status == 1 ||*status ==2) && flag ==1){ // si ya se disparo en la casilla, pero se quiere usar cualquier otro disparo y esta casilla es la central
        //https://encrypted-tbn0.gstatic.com/images?q=tbn:ANd9GcTkZrHAIXhsa3L7eLZlp27C8bhrBd3TmcTxfA&s

    } else if ((*status == 1 ||*status ==2) && flag ==2){ //si ya se habia disparado en la casilla, pero esto es la onda expansiva del disparo
        //https://encrypted-tbn0.gstatic.com/images?q=tbn:ANd9GcTkZrHAIXhsa3L7eLZlp27C8bhrBd3TmcTxfA&s
    }
}

// cambia el estado de la casilla y muestra en pantalla si se reveló o no un barco
void procesarRadar(int x, int y){
    int *status = (int *)tablero[x][y]; // agarra el estado de la casilla actual
    if (*status == 4){
        *status = 3; // si hay un barco, el estado pasa a descubierto
    } else if(*status == 0){
        *status = 5; // si no hay barco, el estado pasa a no hay barco
    }// como al disparo radar no le interesa si la casilla actual fue disparada o no, hasta aca
}


//si procesarDisparo impacto a un enemigo, revisa cada barco, y anula las coordenadas del barco correspondiente
void ProcesarCasillasAfectadas(int x,int y){
    for(int i=0; i<numbarcos;i++){
        int k = barcos[i].tamano;
        for(int j=0; j<k ;j++){ // este for se encarga de anular las coordenadas de esta casilla
            if(barcos[i].coordenadas[j].x == x && barcos[i].coordenadas[j].y == y && barcos[i].vivoflag == 1){
                barcos[i].coordenadas[j].x = -1;
                barcos[i].coordenadas[j].y = -1;
            }
        }
        
    }
}

//despues de cada disparo, revisa si algun barco fue eliminado por completo
void procesarBarcosEliminados(){
    for (int i = 0; i < numbarcos; i++) {
        for (int j = 0; j < barcos[i].tamano; j++) {
            // si las casillas de un barco estan en -1, -1, significa que fueron impactadas, se cambian las coordenadas a -2 para que no se vuelvan a contar
            if (barcos[i].coordenadas[j].x == -1 && barcos[i].coordenadas[j].y == -1 && barcos[i].vivoflag == 1) {
                barcos[i].casillas_hundidas++; //suma una casilla hundida
                barcos[i].coordenadas[j].x = -2;
                barcos[i].coordenadas[j].y = -2;
            }
        }
        // si todas las casillas de un barco estan en -2, el barco fue eliminado
        if (barcos[i].casillas_hundidas == barcos[i].tamano && barcos[i].vivoflag == 1) {
            barcos[i].vivoflag = 0; //el barco es eliminado, el flag se cambia para que no se vuelva a contar
            for (int j = 0; j < barcos[i].tamano; j++) {
                barcos[i].coordenadas[j].x = -2;
                barcos[i].coordenadas[j].y = -2; //para que esten eliminados, pero no sirvan mas para el conteo de barcos eliminados
            }
        }
    }
}

//para limpiar memoria del struct Mano
void limpiacartas(){
    free(Cartas.carta); 
    Cartas.carta = NULL;
}