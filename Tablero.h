#ifndef H_TABLERO
#define H_TABLERO

// las coordenadas de cada barco, se guardaran en un arreglo del tamano del barco
typedef struct coordBarcos{
    int x;
    int y;
} coordBarcos;
extern coordBarcos coordenadas;

// cada barco tendra una flag que dira si esta vivo, su tamaño, cuantas casillas hundidas tiene y sus coordenadas
typedef struct Barco{ 
    int vivoflag;
    int tamano;
    int casillas_hundidas;
    coordBarcos *coordenadas;
} Barco; // crea el tipo dato barco
extern Barco *barcos;

extern void *** tablero; // extern = DECLARACION, la variable se DEFINE en otro archivo
// triple puntero = [a][b][c], 3 dimensiones, entonces
/*  
***tablero sera un arreglo con las casillas x, de forma [x1][x2][x3]
**tablero[x] sera un arreglo con las casillas y, de forma [x1]->[y1] [x2]->[y2] [x3]->[y3] 
*tablero[x][y] sera el estatus de la casilla (x,y) actual, de forma [x1][y1]->[0] [x1][y2]->[1] [x1][y3]->[2]
*/

extern int size, limite_turnos;


/*
***
int *r: puntero a entero que servira para guardar la dificultad elegida
...
***
no retorna nada
***
pregunta por la dificultad deseada, y guarda este valor en r
*/
void dificultad(int *r); // r sera la dificultad del juego

/*
***
int r: dificultad del tablero
...
***
no retorna nada
***
inicializa el tablero con la cantidad de casillas y barcos segun la dificultad
*/
void inicializarTablero(int r);

/*
***
int x: coordenada x inicial del barco
int y: coordenada y inicial del barco
int direccion: direccion en la que se posicionara el barco
int tamano: tamaño del barco a colocar
coordBarcos *coordenadas: arreglo de coordenadas del barco
...
***
no retorna nada
***
segun la direccion y el tamaño del barco, coloca el barco partiendo por las coordenadas x,y en el tablero
*/
void posicionaBarcos(int x, int y, int direccion, int tamano, coordBarcos *coordenadas);

/*
***
coordBarcos *coordenadas: arreglo de coordenadas del barco
int tamano: tamaño del barco a colocar
...
***
no retorna nada
***
genera coordenadas al azar para los barcos, llama a verificaPosicionBarcos hasta que las coordenadas
a insertar el barco sean validas
*/
void creaCoordenadasBarcos(coordBarcos coordenadas[], int tamano);

/*
***
int r: dificultad del tablero
...
***
no retorna nada
***
genera la cantidad de barcos y su tamaño segun la dificultad elegida, guarda los datos en el arreglo de barcos
*/
void generaBarcos(int r); 

/*
***
int x: coordenada x del disparo
int y: coordenada y del disparo
int direccion: direccion en la que se posicionara el barco
int tamano: tamaño del barco a colocar
...
***
retorna un int que sirve como flag: si retorna uno, el barco puede ser posicionado, si retorna 0, no se puede y
se llamara de nuevo a esta funcion
***
segun las coordenadas iniciales y la direccion, revisa que cada uno de las casillas donde se posicionara el barco
esten disponibles
*/
int verificaPosicionBarcos(int x, int y, int direccion, int tamano);

/*
***
...
***
no retorna nada
***
analiza el tablero por completo, y muestra por terminal el estado de cada casilla
*/
void mostrarTablero(); 

/*
***
...
***
no retorna nada
***
se encarga de liberar la memoria de los structs Barco, coordBarcos y tablero
*/
void limpiabarcos();
#endif

