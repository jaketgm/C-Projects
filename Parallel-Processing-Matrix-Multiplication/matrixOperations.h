/************************************************************************************
 * Method: createMatrix: This method initializes a square matrix of size N x N by 
 * populating it with random integers. It iterates through each row (i) and each 
 * column (j) of the provided matrix. For each element at position [i][j], it 
 * assigns a random integer value between 0 and 99.
 *
 * Input: int (*matrix)[N].
 *
 * Output: None.
 *
************************************************************************************/
void createMatrix(int (*matrix)[N]) 
{
    int i, j;
    for (i = 0; i < N; i++)
        for (j = 0; j < N; j++)
            matrix[i][j] = rand() % 100;
}

/************************************************************************************
 * Method: multiplyMatricies: This method performs matrix multiplication on two 
 * square matrices (matrixOne and matrixTwo), storing the result in resultantMatrix. 
 * For each cell in the resultantMatrix, it calculates the dot product of the 
 * corresponding row from matrixOne and the corresponding column from matrixTwo. 
 *
 * Input: int (*matrixOne)[N], int (*matrixTwo)[N], int (*resultantMatrix)[N].
 *
 * Output: None.
 *
************************************************************************************/
void multiplyMatricies(int (*matrixOne)[N], int (*matrixTwo)[N], int (*resultantMatrix)[N])
{
    int i, j, k;
    for (i = 0; i < N; i++)
    {
        for (j = 0; j < N; j++)
        {
            resultantMatrix[i][j] = 0;
            for (k = 0; k < N; k++)
                resultantMatrix[i][j] += matrixOne[i][k] * matrixTwo[k][j];
        }
    }
}

/************************************************************************************
 * Method: printMatrixToFile: This method writes the contents of our three matrices 
 * (matrixOne, matrixTwo, resultantMatrix) and the computation time (cpuTime) to the 
 * specified file (filename). It opens the file in write mode, and if successful, 
 * it sequentially writes each matrix in a readable format, followed by the 
 * computation time at the end.
 *
 * Input: int (*matrixOne)[N], int (*matrixTwo)[N], int (*resultantMatrix)[N], 
 * double cpuTime, const char* filename.
 *
 * Output: None.
 *
************************************************************************************/
void printMatrixToFile(int (*matrixOne)[N], int (*matrixTwo)[N], int (*resultantMatrix)[N], double cpuTime, const char* filename)
{
    int i, j;
    FILE *file = fopen(filename, "w");

    if (file == NULL) {
        printf("Error opening file!\n");
        exit(1);
    }

    // Write Matrix One
    fprintf(file, "Matrix One:\n");
    for (i = 0; i < N; i++) {
        for (j = 0; j < N; j++) {
            fprintf(file, "%d ", matrixOne[i][j]);
        }
        fprintf(file, "\n");
    }

    // Write Matrix Two
    fprintf(file, "\nMatrix Two:\n");
    for (i = 0; i < N; i++) {
        for (j = 0; j < N; j++) {
            fprintf(file, "%d ", matrixTwo[i][j]);
        }
        fprintf(file, "\n");
    }

    // Write Resultant Matrix
    fprintf(file, "\nResultant Matrix:\n");
    for (i = 0; i < N; i++) {
        for (j = 0; j < N; j++) {
            fprintf(file, "%d ", resultantMatrix[i][j]);
        }
        fprintf(file, "\n");
    }

    fprintf(file, "\nTime taken (N=%d): %f seconds.\n", N, cpuTime);

    fclose(file);
}