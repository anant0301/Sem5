q3: q3_main.o dictionary.o 
	gcc -o q3  q3_main.o dictionary.o -lpthread 

main.o: main.c
	gcc -c main.c 

dictionary.o: dictionary.c
	gcc -c dictionary.c 

clean:
	rm ./*.o q3