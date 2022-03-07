all: q7

q7: q7_main.o binary_search.o lower_bound.o upper_bound.o random_fill.o
	gcc -o q7 q7_main.o binary_search.o lower_bound.o upper_bound.o random_fill.o

q7_main.o: q7_main.c
	gcc -c q7_main.c

binary_search.o: binary_search.c
	gcc -c binary_search.c

lower_bound.o: lower_bound.c
	gcc -c lower_bound.c

upper_bound.o: upper_bound.c
	gcc -c upper_bound.c

random_fill.o: random_fill.c
	gcc -c random_fill.c

clean:
	rm ./*.o