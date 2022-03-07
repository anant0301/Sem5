all: q5

q5: q5_main.o first_smaller.o first_greater.o sort.o
	gcc -o q5 q5_main.o first_smaller.o first_greater.o sort.o

q5_main.o: q5_main.c
	gcc -c q5_main.c

first_smaller.o: first_smaller.c
	gcc -c first_smaller.c 

first_greater.o: first_greater.c
	gcc -c first_greater.c

sort.o: sort.c
	gcc -c sort.c 
