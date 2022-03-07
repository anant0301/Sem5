all: q7

q7: q7_main.o check_magic_square.o
	gcc -o q7 q7_main.o check_magic_square.o

q7_main.o: q7_main.c
	gcc -c q7_main.c

check_magic_square.o: check_magic_square.c
	gcc -c check_magic_square.c 