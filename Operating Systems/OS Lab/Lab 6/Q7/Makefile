q7: q7_main.o random_point.o 
	gcc -o q7 q7_main.o random_point.o -lpthread

q7_main.o: q7_main.c 
	gcc -c q7_main.c 

random_point.o: random_point.c 
	gcc -c random_point.c 

clean:
	rm ./*.o