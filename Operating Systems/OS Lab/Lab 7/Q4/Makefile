q4: q4_main.o dictionary.o 
	gcc -o q4  q4_main.o dictionary.o -lpthread 

main.o: main.c
	gcc -c main.c 

dictionary.o: dictionary.c
	gcc -c dictionary.c 

clean:
	rm ./*.o q4