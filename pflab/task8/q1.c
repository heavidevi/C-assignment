#include <stdio.h>

int main() {
    // original matrix 
    int original[3][3];
    int transpose[3][3];
    int cofactor[3][3];
    int adjoint[3][3];
    float inverse[3][3];
    
    int determinant = 0;
    int row, col;  
    
    printf("=== COMPLETE MATRIX ANALYSIS PROGRAM ===\n");
    printf("Enter elements of 3x3 matrix:\n");
    
    for (row = 0; row < 3; row++) {
        for (col = 0; col < 3; col++) {
            printf("Enter element [%d][%d]: ", row + 1, col + 1);
            scanf("%d", &original[row][col]);
        }
    }
    
   
    printf("\n--- ORIGINAL MATRIX ---\n");
    for (row = 0; row < 3; row++) {
        printf("| ");
        for (col = 0; col < 3; col++) {
            printf("%6d ", original[row][col]);
        }
        printf("|\n");
    }
    
    printf("\n--- TRANSPOSE MATRIX ---\n");
    for (row = 0; row < 3; row++) {
        for (col = 0; col < 3; col++) {
            transpose[row][col] = original[col][row];  // swap rows and columns
        }
    }

    printf("\n");
    for (row = 0; row < 3; row++) {
        printf("| ");
        for (col = 0; col < 3; col++) {
            printf("%6d ", transpose[row][col]);
        }
        printf("|\n");
    }

    printf("\n");
    printf("\n--- DETERMINANT CALCULATION ---\n");
    

    int term1 = original[0][0] * (original[1][1] * original[2][2] - original[1][2] * original[2][1]);
    int term2 = original[0][1] * (original[1][0] * original[2][2] - original[1][2] * original[2][0]);
    int term3 = original[0][2] * (original[1][0] * original[2][1] - original[1][1] * original[2][0]);
    
    determinant = term1 - term2 + term3;
    
    printf("Term 1: %d * (%d * %d - %d * %d) = %d\n", 
           original[0][0], original[1][1], original[2][2], original[1][2], original[2][1], term1);
    printf("Term 2: %d * (%d * %d - %d * %d) = %d\n", 
           original[0][1], original[1][0], original[2][2], original[1][2], original[2][0], term2);
    printf("Term 3: %d * (%d * %d - %d * %d) = %d\n", 
           original[0][2], original[1][0], original[2][1], original[1][1], original[2][0], term3);
    
    printf("Determinant = %d - %d + %d = %d\n", term1, term2, term3, determinant);
    
   
    printf("\n--- COFACTOR MATRIX ---\n");
    
    for (row = 0; row < 3; row++) {
        for (col = 0; col < 3; col++) {
            int minor[2][2]; 
            int minor_row = 0, minor_col = 0;
            
            for (int matrix_row = 0; matrix_row < 3; matrix_row++) {
                if (matrix_row == row) continue;  
                minor_col = 0;
                for (int matrix_col = 0; matrix_col < 3; matrix_col++) {
                    if (matrix_col == col) continue; 
                    minor[minor_row][minor_col] = original[matrix_row][matrix_col];
                    minor_col++;
                }
                minor_row++;
            }
            
           
            int minor_det = minor[0][0] * minor[1][1] - minor[0][1] * minor[1][0];
          
            int sign = ((row + col) % 2 == 0) ? 1 : -1;
            cofactor[row][col] = sign * minor_det;
            
            printf("Cofactor[%d][%d] = %d * (%d*%d - %d*%d) = %d\n", 
                   row, col, sign, minor[0][0], minor[1][1], minor[0][1], minor[1][0], cofactor[row][col]);
        }
    }
    

    printf("\nCofactor Matrix:\n");
    for (row = 0; row < 3; row++) {
        printf("| ");
        for (col = 0; col < 3; col++) {
            printf("%6d ", cofactor[row][col]);
        }
        printf("|\n");
    }
    
    printf("\n--- ADJOINT MATRIX ---\n");
    for (row = 0; row < 3; row++) {
        for (col = 0; col < 3; col++) {
            adjoint[row][col] = cofactor[col][row]; 
        }
    }
    

    for (row = 0; row < 3; row++) {
        printf("| ");
        for (col = 0; col < 3; col++) {
            printf("%6d ", adjoint[row][col]);
        }
        printf("|\n");
    }
    
    printf("\n--- INVERSE MATRIX ---\n");
    if (determinant == 0) {
        printf("Matrix is singular (determinant = 0). Inverse does not exist.\n");
    } else {
        printf("Inverse = (1/%d) * Adjoint Matrix\n", determinant);
        
       
        for (row = 0; row < 3; row++) {
            for (col = 0; col < 3; col++) {
                inverse[row][col] = (float)adjoint[row][col] / determinant;
            }
        }
        
   
        printf("\nInverse Matrix:\n");
        for (row = 0; row < 3; row++) {
            printf("| ");
            for (col = 0; col < 3; col++) {
                printf("%8.3f ", inverse[row][col]);
            }
            printf("|\n");
        }
        
        printf("\n--- VERIFICATION: Original * Inverse = Identity ---\n");
        float identity[3][3];
        
        for (row = 0; row < 3; row++) {
            for (col = 0; col < 3; col++) {
                identity[row][col] = 0;
                for (int element = 0; element < 3; element++) {
                    identity[row][col] += original[row][element] * inverse[element][col];
                }
            }
        }
        
        for (row = 0; row < 3; row++) {
            printf("| ");
            for (col = 0; col < 3; col++) {
                printf("%8.3f ", identity[row][col]);
            }
            printf("|\n");
        }
    }

    return 0;
}