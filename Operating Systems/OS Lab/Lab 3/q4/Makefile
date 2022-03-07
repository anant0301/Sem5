all: q4

q4: q4.o is_prime.o fib_series.o
	gcc -o q4 q4.o is_prime.o fib_series.o
q4.o: q4.c
	gcc -c q4.c
is_prime.o: is_prime.c
	gcc -c is_prime.c
fib_series.o: fib_series.c
	gcc -c fib_series.c
