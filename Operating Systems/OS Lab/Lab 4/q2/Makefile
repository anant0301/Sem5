all: q2

q2: q2_main.o mergeSort.o mergeBack.o randomfill.o
	gcc -o q2 q2_main.o mergeSort.o mergeBack.o randomfill.o

q2_main.o: q2_main.c
	gcc -c q2_main.c

mergeSort.o: mergeSort.c
	gcc -c  mergeSort.c

mergeBack.o: mergeBack.c
	gcc -c mergeBack.c
	
randomfill.o: randomfill.c
	gcc -c randomfill.c

clean: 
	rm ./*.o