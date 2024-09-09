#include <stdlib.h>
#include <stdio.h>
#include "Cartas.h"
#include "Tablero.h"

extern int size, limite_turnos; //para usar size,turns
extern Mano Cartas;
int turno,x, y;
int selected;



void Battleship(){
    //int x,y;
    turno =1;
    int restantes = numbarcos;
    while (turno < limite_turnos){
        printf("Turno %d\n", turno);
        mostrarTablero();

        printf("Cartas:\n");
        mostrarMazo();
        
        //la funcion preguntara por la carta a usar y las coordenadas a disparar
        usarCarta();
        
        turno +=1;

        //revisa si algun barco fue eliminado por completo, resta uno al contador de barcos vivos y cambia el estado del barco para que no se vuelva a contar
        for (int i =0; i<numbarcos; i++){
            if (barcos[i].vivoflag == 0){
                printf("Barco eliminado\n");
                restantes -=1;
                barcos[i].vivoflag -=1;
            }
        }
        
        printf("Barcos restantes: %d\n", restantes);
        // si se pudo eliminar todos los barcos en los turnos dados, se gana
        if (restantes == 0){
            printf("Victoria en la defensa de Po Inter City\nTablero:\n");
            mostrarTableroFinal();
            return;
        }
    }
    // si no se pudo eliminar todos los barcos, se pierde
    printf("Fracaso en la defensa de Po Inter City\nTablero final:\n");
    mostrarTableroFinal();
    return;
}


int main(int argc, char const *argv[])
{
    //logica de dificultad
    int r;
    dificultad(&r);
    printf("Dificultad: %d\n", r);

    //inicializa el tablero y los barcos
    inicializarTablero(r);
    inicializarMazo();

    //inicia el juego
    Battleship();

    //limpia la memoria
    limpiabarcos();
    limpiacartas();
    return 0;
}
