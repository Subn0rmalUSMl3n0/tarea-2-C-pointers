#ifndef H_CARTAS
#define H_CARTAS

#include "Tablero.h"

typedef struct Mano // empieza a definir el struct Mano
{
    void ** carta; // **: puntero a puntero *, con *: puntero a un arreglo de 5 cartas
    int disponibles;
} Mano; // define el tipo de dato mano, para no tener que usar struct mano

extern Mano Cartas; // mano cartas es una variable mano, que contiene array las 5 cartas disponibles, es una DECLARACION, no DEFINICION
extern int size, x,y, numbarcos, selected; //para usar las variables en Cartas.c

/*
***
...
***
No retorna nada
***
Crea la variable Mano Cartas, y la inicializa con 5 disparos simples
*/
void inicializarMazo(); 

/*
***
...
***
No retorna nada
***
printea las cartas disponibles en Cartas por pantalla
*/
void mostrarMazo();

/*
***
...
***
No retorna nada
***
pregunta por la carta a usar, invoca a la funcion de la carta elegida, y revisa si algun barco fue eliminado
*/
void usarCarta();

/*
***
int x: coordenada x del disparo
int y: coordenada y del disparo
...
***
retorna un puntero a una funcion disparo al azar de todas menos la de 500kg
***
dispara en un area de 1x1 en las coordenadas dadas
*/
void * disparoSimple(int x, int y); 

/*
***
int x: coordenada x del disparo
int y: coordenada y del disparo
...
***
retorna un puntero a una funcion disparo al azar
***
dispara en un area de 3x3 con centro en las coordenadas
*/
void * disparoGrande(int x, int y); 

/*
***
int x: coordenada x del disparo
int y: coordenada y del disparo
...
***
retorna un puntero a una funcion disparo al azar
***
dispara en un area de 1x5 en linea recta con centro en las coordenadas, preguntando si la direccion de disparo es horizontal o vertical
*/
void * disparoLineal(int x, int y); 

/*
***
int x: coordenada x del disparo
int y: coordenada y del disparo
...
***
retorna un puntero a una funcion disparo al azar
***
revisa en un area de 5x5 con centro en las coordenadas, mostrando si las casillas afectadas tienen o no barcos
*/
void * disparoRadar(int x, int y); 

/*
***
int x: coordenada x del disparo
int y: coordenada y del disparo
...
***
retorna una carta ya existente en la mano, pues se deja la carta de 500kg actual en ultima posicion, 
asi que se intercambian las posiciones de cartas en la Mano
***
dispara en un area de 11x11 con centro en las coordenadas, elimina la carta de 500kg del mazo, 
achica el tamaño de la mano disponible en 1
*/
void * disparo500KG(int x, int y); 



//LOGICA DE DISPAROS

/*
***
int x: coordenada x del disparo
int y: coordenada y del disparo
int tipo: tipo de disparo a preparar
...
***
no retorna nada
***
dicta la cantidad y coordenadas de casillas que seran afectadas, segun el tipo de disparo recibido
*/
void preparacionesDisparo(int x, int y, int tipo);
/*
***
int x: coordenada x del disparo
int y: coordenada y del disparo
int flag: para evitar disparar en la misma ubicacion, si el disparo es un disparoSimple
...
***
no retorna nada
***
analiza cada casilla recibida por preparacionesDisparo, y cambia el estatus de la casilla segun lo que haya pasado
*/
void Disparo(int x, int y, int flag);


/*
***
int x: coordenada x del disparo
int y: coordenada y del disparo
...
***
no retorna nada
***
revisa las 5x5 casillas alrededor de las coordenadas x,y, y muestra por terminal si hay o no barcos en esa area
*/
void procesarRadar(int x, int y); //logica especifica para el disparo radar


/*
***
int x: coordenada x del disparo
int y: coordenada y del disparo
...
***
no retorna nada
***
si un barco recibio un impacto, se busca el barco afectado en el struct Barcos, y las coordenadas de la casilla
cambian a -1, para indicar que esta casilla esta hundida
*/
void ProcesarCasillasAfectadas(int x, int y);

/*
***
...
***
no retorna nada
***
despues de cada disparo, revisa cada barco de Barco structs a ver si todas sus casillas estan hundidas,
si es asi, resta uno al contador de barcos vivos
*/
void procesarBarcosEliminados();// revisa si algun barco fue eliminado por completo


/*
***
...
***
no retorna nada
***
Luego de acabar el juego, limpia la memoria del struct Mano
*/
void limpiacartas();


#endif