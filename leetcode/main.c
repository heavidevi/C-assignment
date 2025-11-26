#include <stdio.h>
#include <stdlib.h>

void rotate(int** matrix, int matrixSize, int* matrixColSize) {
    int maxsize = matrixSize -1;
    for (int i =0;i<maxsize;i++){
        for (int j =i;j<maxsize -i;j++){
            int temp = matrix[i][j];
            matrix[i][j] = matrix[maxsize -j][i];
            matrix[maxsize -j][i] = matrix[maxsize -i][maxsize -j];
            matrix[maxsize -i][maxsize -j] = matrix[j][maxsize -i];
            matrix[j][maxsize -i] = temp;
        }
    }
}

int main(){
    int matrix[3][3] = {
        {1, 2, 3},
        {4, 5, 6},
        {7, 8, 9}
    };
    int* matrixPtr[3];
    for (int i = 0; i < 3; i++) {
        matrixPtr[i] = matrix[i];
    }
    int matrixSize = 3;
    int matrixColSize = 3;
    rotate(matrixPtr, matrixSize, &matrixColSize);
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            printf("%d ", matrixPtr[i][j]);
        }
        printf("\n");
    }
    return 0;
}