all: quickSort

variables = quickSort_main.o randomfill.o qSort

quickSort: $(variables) 
	gcc -o quickSort $(variables) 

quickSort_main.o: quickSort_main.c
	gcc -c quickSort_main.c

randomfill.o: randomfill.c
	gcc -c randomfill.c

qSort.o: qSort.c
	gcc -c qSort.c
