all: calc format
calc: calc.c
	gcc -Wall -o calc calc.c 
format: format.c 
	gcc -Wall -o  format format.c
clean:
	rm -rf format.o calc.o

