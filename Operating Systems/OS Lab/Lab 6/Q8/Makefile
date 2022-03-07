q8: q8_main.o random_fill.o determinant.o inverse.o cofactor.o 
	gcc -o q8 q8_main.o random_fill.o determinant.o inverse.o cofactor.o -lpthread 

q8_main.o: q8_main.c 
	gcc -c q8_main.c 

random_fill.o: random_fill.c 
	gcc -c random_fill.c 

determinant.o: determinant.c 
	gcc -c determinant.c 

inverse.o: inverse.c 
	gcc -c inverse.c 

cofactor.o: cofactor.c 
	gcc -c cofactor.c 

clean:
	rm ./*.o