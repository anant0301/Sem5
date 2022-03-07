q6: q6_main.o merge_sort.o quick_sort.o 
	gcc -o q6 q6_main.o merge_sort.o quick_sort.o -lpthread 

q6_main.o: q6_main.c 
	gcc -c q6_main.c 

merge_sort.o: merge_sort.c 
	gcc -c merge_sort.c 

quick_sort.o: quick_sort.c 
	gcc -c quick_sort.c 

clean:
	rm *.o