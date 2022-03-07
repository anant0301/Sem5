all: q5 q6 q7 q8 q9 

q5: ./Q5/q5_main.o ./Q5/get_sum.o headers.h
	gcc -o q5 ./Q5/q5_main.o ./Q5/get_sum.o -lpthread

q5_main.o: ./q5_main.c 
	gcc -c ./q5_main.c 

get_sum.o: ./get_sum.c 
	gcc -c ./get_sum.c

q6: ./Q6/q6_main.o ./Q6/sort.o 
	gcc -o q6 ./Q6/q6_main.o ./Q6/sort.o -lpthread 

q6_main.o: ./q6_main.c 
	gcc -c ./q6_main.c 

sort.o: ./sort.c 
	gcc -c ./sort.c 

q7: ./Q7_2/q7_main.c ./Q7_2/header_q7_1.h ./Q7_2/binary_search.c ./Q7_2/random_fill.c
	gcc -o q7 ./Q7_2/q7_main.c ./Q7_2/header_q7_1.h ./Q7_2/binary_search.c ./Q7_2/random_fill.c -lpthread

q7_main.o: ./q7_main.c 
	gcc -c ./q7_main.c 

binary_search.o: ./binary_search.c 
	gcc -c ./binary_search.c 

random_fill.o: random_fill.c 
	gcc -c random_fill.c 

q8: ./Q8/q8_main.o ./Q8/fib_series_parallel.o ./Q8/fibonacci_series.o 
	gcc -o q8 ./Q8/q8_main.o ./Q8/fib_series_parallel.o ./Q8/fibonacci_series.o  -lpthread

q8_main.o: q8_main.c
	gcc -c q8_main.c

fib_series_parallel.o: fib_series_parallel.c 
	gcc -c fib_series_parallel.c 

fibonacci_series.o: fibonacci_series.c 
	gcc -c fibonacci_series.c 

q9: ./Q9/q9_main.o ./Q9/longest_common_subsequence.o 
	gcc -o q9 ./Q9/q9_main.o ./Q9/longest_common_subsequence.o -lpthread

q9_main.o: q9_main.c 
	gcc -c q9_main.c 

longest_common_subsequence.o: longest_common_subsequence.c 
	gcc -c longest_common_subsequence.c 

clean: 
	rm -rf ./*/*.o
