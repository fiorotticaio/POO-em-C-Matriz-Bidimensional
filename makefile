prog: clean main.o
	gcc -o prog main.o numero.o matriz.o 
	./prog

main.o: numero.o matriz.o
	gcc -c main.c 

numero.o: 
	gcc -c numero.c

matriz:
	gcc -c matriz.c

clean:
	rm -rf *.o *~ prog
