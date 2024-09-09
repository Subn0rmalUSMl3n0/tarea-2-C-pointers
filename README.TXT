Ricardo Ruz, 202373567-1

Para ejecutar el programa, asegurarse de haber descomprimido el archivo .tar.gz
Para compilar se usará gcc 9.4.0

Abrir la terminal, estando a la altura de los archivos, escribir "make" en la terminal, y luego "./Battleship.exe"
Después, seguir las instrucciones dadas en pantalla

Si se quiere limpiar los archivos creados por el Makefile, escribir "make clean"
Si se quiere analizar el programa en busca de leaks de memoria, escribir "make valgrind"

Para efectos del programa:
" " implica que esta casilla no ha sido disparada
"X" implica que el disparo acertó a un barco
"O" implica que el disparó falló
"-" implica que el radar no encontró nada en esta casilla
"!" implica que el radar encontró un barco en esta casilla