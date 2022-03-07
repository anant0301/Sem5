#ifndef headers
#define headers

/*	provides standard input output functions 
here: printf() and scanf()	*/
#include<stdio.h>
/*	provides standard function in the library 
here: atoi(), remove() and rand(), includes data type pid_t	*/
#include<stdlib.h>
/*	provides access to the POSIX operating system API 
here: fork()	*/
#include<unistd.h>
/*	provides symbolic constants for use with waitpid(): WNOHANG,etc 
here: waitpid()	*/
#include<sys/wait.h>

/* 	limits the values in the matrix	*/
#define RANDOM_NUMBER_LIMIT 100

/*	the matrix structure 	*/
struct matrix
{
	int **arr; 	// for 2-D array
	int row;	// no of rows
	int col;	// no of cols
};

/*	create a matrix of dimension row*col*/
struct matrix* createMatrix(int row, int col);
/* 	randomly fill the values in the matrix 	*/
int randomfill(struct matrix *mat);
/* 	print the matrix	*/
int printMatrix(struct matrix *m);
/*	multiply the matrix and return the product matrix	*/
struct matrix* matrixMultiply(struct matrix *m1, struct matrix *m2);
/*	element-wise multiplication of the row of m1 to col of m2	*/
int multiply_row_col(struct matrix *m1, int row, struct matrix *m2, int col);
/*	write from file to matrix	*/
int write_to_matrix(struct matrix* m, char fileName[]);

#endif