all: q5

q5: q5_main.o linear_search.o uniq_element.o
	gcc -o q5 q5_main.o linear_search.o uniq_element.o

q5_main.o: q5_main.c
	gcc -c q5_main.c

linear_search.o: linear_search.c
	gcc -c linear_search.c

uniq_element.o: uniq_element.c
	gcc -c uniq_element.c