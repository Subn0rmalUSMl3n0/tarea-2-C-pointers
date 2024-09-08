#include <stdlib.h>
#include <stdio.h>
#include "Cartas.h"
#include "Tablero.h"

extern int size, limite_turnos,u; //para usar size,turns
extern Mano Cartas;
int turno,x, y;
int El_Prohibido = -1;

void Battleship(){
    //int x,y;
    turno =1;
    int selected;
    while (turno < limite_turnos){
        printf("Turno %d\n", turno);
        mostrarTablero();

        printf("Cartas:\n");
        mostrarMazo();

        do{
            printf("Seleccione una carta: ");
            scanf("%d", &selected);
            if (selected < 1 || selected > 5) printf("Carta no valida, por favor intente de nuevo\n");
            if (selected-1 == El_Prohibido) printf("Carta no disponible, por favor intente de nuevo\n");
        }while(selected < 1 || selected > 5 || El_Prohibido == selected-1);
        do{
            printf("Selecciona Coordenadas:\nX:");
            scanf("%d", &x);
            printf("Y:");
            scanf("%d", &y);
            if (x> size || y>size) printf("Coordenadas fuera de rango, por favor intente de nuevo\n");
        }while (x>size || y>size);
        void * (*puntero_disparos)(int, int) = Cartas.carta[selected-1]; //crea variable que apuntara al disparo elegido
        Cartas.carta[selected-1] = (void *) (*puntero_disparos)(x-1,y-1); //invoca funcion de carta elegita
        if (Cartas.carta[selected-1] == disparo500KG){
            El_Prohibido = selected-1;
            printf("Carta %d eliminada\n", selected-1);
        }
        turno +=1;
        printf("Barcos restantes: %d\n", vivos);
        if (vivos == 0){
            printf("Victoria en la defensa de Po Inter City!!!!111!!!1!!!!\n");
            return;
        }
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
