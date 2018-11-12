myas: main.o trans.o check.o
	gcc -o myas main.o trans.o check.o -lm

main.o: main.c
	gcc -O -Wall -c main.c

trans.o: trans.c
	gcc -O -Wall -c trans.c

check.o: check.c
	gcc -O -Wall -c check.c

clean:
	rm -f main.o trans.o check.o myas
