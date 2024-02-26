vent.o: vent.h eolienne.h vent.c
	gcc -c vent.c
menu.o: menu.h vent.h eolienne.h menu.c
	gcc -c menu.c
eolienne.o: eolienne.h menu.h vent.h eolienne.c
	gcc -c eolienne.c
eolienne: eolienne.o vent.o menu.o
	gcc eolienne.o vent.o menu.o -o eolienne