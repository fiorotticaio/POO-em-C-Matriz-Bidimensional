prog: clean main.o
	gcc -o prog main.o numero.o matriz.o  -pedantic
	./prog

main.o: numero.o matriz.o
	gcc -c main.c -pedantic

numero.o: 
	gcc -c numero.c -pedantic

matriz:
	gcc -c matriz.c -pedantic

clean:
	rm -rf *.o *~ prog
