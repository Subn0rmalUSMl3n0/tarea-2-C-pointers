#ifndef H_CARTAS
#define H_CARTAS

#include "Tablero.h"
typedef struct Mano // empieza a definir el struct Mano
{
    void ** carta; // **: puntero a puntero *, con *: puntero a un arreglo de 5 cartas
    int disponibles;
} Mano; // define el tipo de dato mano, para no tener que usar struct mano

extern Mano Cartas; // mano cartas es una variable mano, que contiene array las 5 cartas disponibles, es una DECLARACION, no DEFINICION
void inicializarMazo(); // empieza la mano con 5 disparos simples
void mostrarMazo(); //printea las cartas en la mano
void usarCarta(); // usa carta de la mano, se debe preguntar cual se quiere usar, debe ser reemplazada tras uso

// Disparos, todos deben tener centro en (x,y)
void * disparoSimple(int x, int y); // A= 1x1, simple = 65%, grande = 20%, linea = 5%, radar = 10%
void * disparoGrande(int x, int y); // A = 3x3, simple = 80, grande =3, lineal = 10, radar = 5, helldivers = 2
void * disparoLineal(int x, int y); // A = 1x5 o 5x1, preguntar si tiro es horizontal o vertical, simple 85, grande 5, lineal 2, radar 6, helldivers 2
void * disparoRadar(int x, int y); // A = 5x5, simple 75, grande 15, lineal 5, radar 2, helldivers 3
void * disparo500KG(int x, int y); // A = 11x11, solo se obtiene una vez (tirarle flag con malloc?), mata el cañon y no retorna nada
void * brokenCannon(int x, int y); // no se puede disparar, solo se obtiene si se usa 500KG
void procesarDisparo(int x, int y, int flag); // procesa el disparo, llama a la funcion correspondiente
void preparacionesDisparo(int x, int y, int tipo); // prepara el disparo, llama a la funcion correspondiente
void procesarBarcosEliminados(int x, int y); // procesa los barcos eliminados
void procesarRadar(int x, int y);
extern int size,limite_turnos, x,y; //para usar size,turns
extern int vivos;

#endif