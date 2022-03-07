all: q4

q4: q4_main.o input.o
	gcc -o q4 q4_main.o input.o

q4_main.o: q4_main.c 
	gcc -c q4_main.c

input.o: input.c
	gcc -c input.c
