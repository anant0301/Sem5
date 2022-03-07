all: q6

q6: q6_main.o printMatrix.o randomfill.o multiply_row_col.o matrixMultiply.o createMatrix.o write_to_matrix.o
	gcc -o q6 q6_main.o printMatrix.o randomfill.o multiply_row_col.o matrixMultiply.o createMatrix.o write_to_matrix.o

q6_main.o: q6_main.c 
	gcc -c q6_main.c

matrixMultiply.o: matrixMultiply.c 
	gcc -c matrixMultiply.c

createMatrix.o: createMatrix.c 
	gcc -c createMatrix.c

printMatrix.o: printMatrix.c 
	gcc -c printMatrix.c

randomfill.o: randomfill.c
	gcc -c randomfill.c

write_to_matrix.o: write_to_matrix.c
	gcc -c write_to_matrix.c

multiply_row_col.o: multiply_row_col.c
	gcc -c multiply_row_col.c

clean: 
	rm ./*.o