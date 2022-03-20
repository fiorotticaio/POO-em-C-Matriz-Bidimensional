all: prog valgrind clean
	./prog

prog: main.o
	./prog

main.o: clean numero.o matriz.o
	gcc -c main.c -pedantic
	gcc -o prog main.o numero.o matriz.o -lm -pedantic

numero.o: 
	gcc -c numero.c -pedantic

matriz:
	gcc -c matriz.c -lm -pedantic

clean:
	rm -rf *.o *~ prog

valgrind: main.o
	valgrind ./prog
