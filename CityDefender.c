#include <stdlib.h>
#include <stdio.h>
#include "Cartas.h"
#include "Tablero.h"

extern int size, limite_turnos,u; //para usar size,turns
extern Mano Cartas;
int turno;
int x, y;

void Battleship(){
    //int x,y;
    turno =1;
    int selected;
    while (turno < limite_turnos){
        printf("Turno %d\n", turno);
        mostrarTablero();

        printf("Cartas:\n");
        mostrarMazo();

        printf("Seleccione una carta: ");
        scanf("%d", &selected);
        printf("Selecciona Coordenadas:\nX:");
        scanf("%d", &x);
        printf("Y:");
        scanf("%d", &y);
    
        void (*puntero_disparos)(int, int) = Cartas.carta[selected-1]; //crea variable que apuntara al disparo elegido
        (*puntero_disparos)(x-1,y-1); //invoca funcion de carta elegita
        turno +=1;
    }
    printf("Fracaso en la defensa de Po Inter City\n");
    inicializarMazo();
    return;
}


int main(int argc, char const *argv[])
{
    int r;
    dificultad(&r);
    printf("Dificultad: %d\n", r);
    inicializarTablero(r);
    inicializarMazo();
    Battleship();
    return 0;
}
