#ifndef H_TABLERO
#define H_TABLERO


typedef struct coordBarcos{
    int x;
    int y;
} coordBarcos;
extern coordBarcos coordenadas;

typedef struct Barco{
    int tamano;
    coordBarcos *coordenadas;
} Barco; // crea el tipo dato barco
extern Barco *barcos;

extern void *** tablero; // extern = DECLARACION, la variable se DEFINE en otro archivo
// triple puntero = [a][b][c], 3 dimensiones, entonces
/*  
***tablero sera un arreglo de n*m casillas, con cada casilla siendo marcada por el arreglo [(x1,y1),(x1,y2),...(xn,ym)] 
**tablero[a] sera un arreglo que dira si la casilla (xi,yj) no ha sido disparada, si fallo o si acerto, de la forma [(xi,yj)] -> [estatus]
*tablero[a][b] seran los barcos que usen [(x1,y1),(x2,y2),...] casillas dentro del tablero, y su estado actual se vera de la forma 
    [(xi,yj)] -> [estatus] -> [(x1,y1),(x2,y2),...], para ver si la casilla actual contiene o no un barco, y si esta o no hundido
*/
extern int size, limite_turnos; //para usar size,turns
void dificultad(int *r); // pregunta la dificultad del juego se guarda en r

void inicializarTablero(int tamano); //inicializa el tablero para el tamaño que se pregunte
void mostrarTablero(); // printea el estado actual del tablero, ' ' si no se ha disparado, 'X' si fallo, 'O' si acerto

void generaBarcos(int u);

int compruebaBarcos(int x, int y, int direccion, int tamano);
void posicionaBarcos(int x, int y, int direccion, int tamano, coordBarcos *coordenadas);

void imprimirCoordenadasBarcos(Barco *coordsbarcos, int numbarcos);
#endif


// se debe preguntar el tamaño del tablero antes de inicializarlo:
/* F´acil: Un tablero de 11 × 11, con 30 turnos y
2 barcos tamaño 1 × 2, 
1 de 1 × 3, 
1 de 1 × 4
1 de 1 × 5*/

/*Medio: Un tablero de 17 × 17, con 25 turnos y
3 barcos tama;o 1 × 2, 
2 de 1 × 3, 
1 de 1 × 4
1 de 1 × 5*/

/*Dif´ıcil: Un tablero de 21 × 21, con 15 turnos y
3 barcos de tamano 1 × 2, 
2 de 1 × 3,
2 de 1 × 4 
2 de 1 × 5*/