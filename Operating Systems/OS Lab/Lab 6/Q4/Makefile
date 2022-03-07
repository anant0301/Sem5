q4: q4_main.o is_prime.o
	gcc -o q4 q4_main.o is_prime.o -lpthread

q4_main.o: q4_main.c 
	gcc -c q4_main.c

is_prime.o: is_prime.c 
	gcc -c is_prime.c

clean: 
	rm *.o