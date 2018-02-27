//Kevin Nguyen
//kdn433

/* 
 * trans.c - Matrix transpose B = A^T
 *
 * Each transpose function must have a prototype of the form:
 * void trans(int M, int N, int A[N][M], int B[M][N]);
 *
 * A transpose function is evaluated by counting the number of misses
 * on a 1KB direct mapped cache with a block size of 32 bytes.
 */ 
#include <stdio.h>
#include "cachelab.h"

int is_transpose(int M, int N, int A[N][M], int B[M][N]);

/* 
 * transpose_submit - This is the solution transpose function that you
 *     will be graded on for Part B of the assignment. Do not change
 *     the description string "Transpose submission", as the driver
 *     searches for that string to identify the transpose function to
 *     be graded. 
 */
char transpose_submit_desc[] = "Transpose submission";
void transpose_submit(int M, int N, int A[N][M], int B[M][N])
{
	//Local declarations of variables to use
	int row, column, blockRowSize, blockColSize, blockSize, limitRow, limitCol, tmp, tmp2, diagonalPos;
	
	//First if case is considered only on even square matrices, all other cases of odd or uneven sizes are in else case
	if((M == N) && ((M % 2) == 0)) {
		//BlockSize is the size of the subset in the matrix
		//Case depends if matrix is 32x32 or 64x64 in size; set blockSize accordingly
		//Note: 64x64 gives the trickiest case, but blockSize of 4 yields the best results at the moment...
		if (M == 32) {
			blockSize = 8;
		}
		else if (M == 64) {
			blockSize = 4;
		}
		
		//The first two loops gives the range and scope the individual blocks so we don't need to focus on the entire matrix
		for (blockRowSize = 0; blockRowSize < M; blockRowSize = blockRowSize + blockSize) {
			for (blockColSize = 0; blockColSize < N; blockColSize = blockColSize + blockSize) {
				limitRow = blockRowSize + blockSize;
				limitCol = blockColSize + blockSize;

				//The next two loops will help transpose our block
				for (row = blockRowSize; row < limitRow; row++) {
					for (column = blockColSize; column < limitCol; column++) {
						//Transpose everything, but the diagonals of the block matrix, indexing a diag misses alot
						if(row != column) {
							tmp = A[row][column];
							B[column][row] = tmp;
						}
						else {
							tmp2 = A[row][column];
							diagonalPos = row;
						}
					}
					//Diagonal elements so put into B and finish, Diagonals don't change in Tranpose matrices
					if (blockRowSize == blockColSize) {
						B[diagonalPos][diagonalPos] = tmp2;
					}
				}
			}
		}
	}
	else {
		//blockSize is the subset of the matrix size; blocks won't cover entire uneven matrix
		blockSize = 18;
		
		//First two loops gives the range and scope of the individual blocks
		for (blockRowSize = 0; blockRowSize < M; blockRowSize = blockRowSize + blockSize) {
			for (blockColSize = 0; blockColSize < N; blockColSize = blockColSize + blockSize) {
				limitRow = blockRowSize + blockSize;
				limitCol = blockColSize + blockSize;

				//Blocks are subsets of the bigger matrix 
				//transpose the blocks but provide a bounds check so we don't go out-of-bounds
				for (row = blockRowSize; row < limitRow; row++) {
					for (column = blockColSize; column < limitCol; column++) {
						if (row < 61 && column < 67) {
							tmp = A[column][row];
							B[row][column] = tmp;
						}
					}
				}
			}
		}
	}
}

/* 
 * You can define additional transpose functions below. We've defined
 * a simple one below to help you get started. 
 */ 

/* 
 * trans - A simple baseline transpose function, not optimized for the cache.
 */
char trans_desc[] = "Simple row-wise scan transpose";
void trans(int M, int N, int A[N][M], int B[M][N])
{
    int i, j, tmp;

    for (i = 0; i < N; i++) {
        for (j = 0; j < M; j++) {
            tmp = A[i][j];
            B[j][i] = tmp;
        }
    }    

}

/*
 * registerFunctions - This function registers your transpose
 *     functions with the driver.  At runtime, the driver will
 *     evaluate each of the registered functions and summarize their
 *     performance. This is a handy way to experiment with different
 *     transpose strategies.
 */
void registerFunctions()
{
    /* Register your solution function */
    registerTransFunction(transpose_submit, transpose_submit_desc); 

    /* Register any additional transpose functions */
    registerTransFunction(trans, trans_desc); 

}

/* 
 * is_transpose - This helper function checks if B is the transpose of
 *     A. You can check the correctness of your transpose by calling
 *     it before returning from the transpose function.
 */
int is_transpose(int M, int N, int A[N][M], int B[M][N])
{
    int i, j;

    for (i = 0; i < N; i++) {
        for (j = 0; j < M; ++j) {
            if (A[i][j] != B[j][i]) {
                return 0;
            }
        }
    }
    return 1;
}

