all: Battleship.exe #este el nombre del exe

Battleship.exe: CityDefender.o Tablero.o Cartas.o #el exe depende de estos 3 archivos .o = objetos, el -Wall es para que printee los warnings que ocurren al compilar
	gcc -Wall -o Battleship.exe CityDefender.o Tablero.o Cartas.o

CityDefender.o: CityDefender.c
	gcc -c -Wall CityDefender.c

Cartas.o: Cartas.c
	gcc -c -Wall Cartas.c

Tablero.o: Tablero.c
	gcc -c -Wall Tablero.c

clean: #borra los archivos .o
	rm CityDefender.o
	rm Cartas.o
	rm Tablero.o
	rm Battleship.exe

valgrind: Battleship.exe
	valgrind --leak-check=full ./Battleship.exe