all: q8

q8: q8_main.o fibonacci_series.o fib_series_parallel.o cfileexists.o
	gcc -o q8 q8_main.o fibonacci_series.o fib_series_parallel.o cfileexists.o

q8_main.o: q8_main.c
	gcc -c q8_main.c

fibonacci_series.o: fibonacci_series.c
	gcc -c fibonacci_series.c

fib_series_parallel.o: fib_series_parallel.c
	gcc -c fib_series_parallel.c

cfileexists.o: cfileexists.c
	gcc -c cfileexists.c