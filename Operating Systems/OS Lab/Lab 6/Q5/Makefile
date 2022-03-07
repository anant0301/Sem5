all: q5

q5: q5_main.o mean.o median.o mode.o random_fill.o ../Q6/merge_sort.o ../threads/Q7_2/binary_search.o 
	gcc -o q5 q5_main.o mean.o median.o mode.o random_fill.o ../Q6/merge_sort.o ../threads/Q7_2/binary_search.o -lpthread 

q5_main.o: q5_main.c 
	gcc -c q5_main.c 

mean.o: mean.c 
	gcc -c mean.c 

median.o: median.c 
	gcc -c median.c 

mode.o: mode.c 
	gcc -c mode.c 

random_fill.o: random_fill.c 
	gcc -c random_fill.c 

merge_sort.o: merge_sort.c 
	gcc -c merge_sort.c 

binary_search.o: binary_search.c 
	gcc -c binary_search.c 

clean:
	rm *.o