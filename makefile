main: main.o grille.o io.o jeu.o
	gcc -g -Wall -o main.o io.o jeu.o grille.o
main.o: main.c grille.h io.h jeu.h
	gcc -g -Wall -c main.c
io.o: io.c io.h grille.h jeu.h
	gcc -g -Wall -c io.c
jeu.o: jeu.c jeu.h grille.h
	gcc -g -Wall -c jeu.c	
grille.o: grille.c
	gcc -g -Wall -c grille.c
	
version := $(shell git describe --abbrev=0)
dist:
	tar -Jcvf SaoudiSalem-GoL-$(version).tar.xz Doxyfile makefile *.c *.h

docs:
	@doxygen ./Doxyfile

clean:
	rm *.o *.exe main
