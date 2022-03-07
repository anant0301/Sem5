all: q6 clean

q6: q6_main.o first_smaller.o first_greater.o sort.o
	gcc -o q6 q6_main.o first_smaller.o first_greater.o sort.o

q6_main.o: q6_main.c
	gcc -c q6_main.c

first_smaller.o: first_smaller.c
	gcc -c first_smaller.c 

first_greater.o: first_greater.c
	gcc -c first_greater.c

sort.o: sort.c
	gcc -c sort.c 

clean:
	rm ./*.o