#include <stdio.h>
#include <math.h>


int main() {
   
    int matrix[5][5];
    int matrix_square[5][5];  
    int rows, cols;
    int Erow, Ecol;  


    printf("COMPLETE MATRIX TYPE\n");
    printf("Enter number of rows (1-5): ");
    scanf("%d", &rows);
    printf("Enter number of columns (1-5): ");
    scanf("%d", &cols);
   
    printf("\nenter matrix elements:\n");
    for (Erow = 0; Erow < rows; Erow++) {
        for (Ecol = 0; Ecol < cols; Ecol++) {
            printf("Enter element [%d][%d]: ", Erow + 1, Ecol + 1);
            scanf("%d", &matrix[Erow][Ecol]);
        }
    }




    printf("\nMATRIX\n");
    for (Erow = 0; Erow < rows; Erow++) {
        printf("| ");
        for (Ecol = 0; Ecol < cols; Ecol++) {
            printf("%6d ", matrix[Erow][Ecol]);
        }
        printf("|\n");
    }
   
    printf("\nMATRIX TYPE\n");
   
    // 1. square matrix check
    printf("1. SQUARE MATRIX: ");
    int is_square = (rows == cols) ? 1 : 0;
    if (is_square) {
        printf("YES (rows = columns = %d)\n", rows);
    } else {
        printf("NO (rows=%d, columns=%d)\n", rows, cols);
    }
   
    // 2. rectangular matrix check
    printf("2. RECTANGULAR MATRIX: ");
    if (is_square) {
        printf("YES:matrix is a square\n");
    } else {
        printf("NO\n");
    }
   
    // 3. zero/null matrix check
    printf("3. ZERO/NULL MATRIX: ");
    int is_zero = 1;
    for (Erow = 0; Erow < rows && is_zero; Erow++) {
        for (Ecol = 0; Ecol < cols && is_zero; Ecol++) {
            if (matrix[Erow][Ecol] != 0) {
                is_zero = 0;
            }
        }
    }
    printf("%s (all elements %s zero)\n",
           is_zero ? "YES" : "NO",
           is_zero ? "are" : "are not");
   
    // 4. identity matrix check
    printf("4. IDENTITY MATRIX: ");
    int is_identity = 0;
    if (is_square) {
        is_identity = 1;
        for (Erow = 0; Erow < rows && is_identity; Erow++) {
            for (Ecol = 0; Ecol < cols && is_identity; Ecol++) {
                if (Erow == Ecol) {
                   
                    if (matrix[Erow][Ecol] != 1) {
                        is_identity = 0;
                    }
                } else {
                   
                    if (matrix[Erow][Ecol] != 0) {
                        is_identity = 0;
                    }
                }
            }
        }
        printf("%s\n", is_identity ? "YES" : "NO");
    } else {
        printf("NO (not a square matrix)\n");
    }
   
    // 5. diagonal matrix check
    printf("5. DIAGONAL MATRIX: ");
    int is_diagonal = 0;
    if (is_square) {
        is_diagonal = 1;
        for (Erow = 0; Erow < rows && is_diagonal; Erow++) {
            for (Ecol = 0; Ecol < cols && is_diagonal; Ecol++) {
                if (Erow != Ecol && matrix[Erow][Ecol] != 0) {
                    is_diagonal = 0;
                }
            }
        }
        printf("%s (non-diagonal elements %s zero)\n",
               is_diagonal ? "YES" : "NO",
               is_diagonal ? "are all" : "are not all");
    } else {
        printf("NO (not a square matrix)\n");
    }
   
    // 6. scalar matrix check
    printf("6. SCALAR MATRIX: ");
    int is_scalar = 0;
    if (is_square) {
       
        int temp_diagonal = 1;  
        int first_diagonal = matrix[0][0];


        // all non-diagonal elements are zero
        for (Erow = 0; Erow < rows && temp_diagonal; Erow++) {
            for (Ecol = 0; Ecol < cols && temp_diagonal; Ecol++) {
                if (Erow != Ecol && matrix[Erow][Ecol] != 0) {
                    temp_diagonal = 0;
                }
            }
        }
       
        // Check if all diagonal elements are equal
        if (temp_diagonal) {
            is_scalar = 1;
            for (Erow = 1; Erow < rows && is_scalar; Erow++) {
                if (matrix[Erow][Erow] != first_diagonal) {
                    is_scalar = 0;
                }
            }
        }
       
        printf("%s\n", is_scalar ? "YES" : "NO");
        if (is_scalar) {
            printf("   (All diagonal elements = %d, non-diagonal elements = 0)\n", first_diagonal);
        }
    } else {
        printf("NO (not a square matrix)\n");
    }
   
    // 7. upper triangular matrix check
    printf("7. UPPER TRIANGULAR MATRIX: ");
    int is_upper_triangular = 0;
    if (is_square) {
        is_upper_triangular = 1;
        for (Erow = 1; Erow < rows && is_upper_triangular; Erow++) {
            for (Ecol = 0; Ecol < Erow && is_upper_triangular; Ecol++) {
                if (matrix[Erow][Ecol] != 0) {
                    is_upper_triangular = 0;
                }
            }
        }
        printf("%s (elements below diagonal %s zero)\n",
               is_upper_triangular ? "YES" : "NO",
               is_upper_triangular ? "are all" : "are not all");
    } else {
        printf("NO (not a square matrix)\n");
    }
   
    // 8. lower triangular matrix check
    printf("8. LOWER TRIANGULAR MATRIX: ");
    int is_lower_triangular = 0;
    if (is_square) {
        is_lower_triangular = 1;
        for (Erow = 0; Erow < rows - 1 && is_lower_triangular; Erow++) {
            for (Ecol = Erow + 1; Ecol < cols && is_lower_triangular; Ecol++) {
                if (matrix[Erow][Ecol] != 0) {
                    is_lower_triangular = 0;
                }
            }
        }
        printf("%s (elements above diagonal %s zero)\n",
               is_lower_triangular ? "YES" : "NO",
               is_lower_triangular ? "are all" : "are not all");
    } else {
        printf("NO : not a square matrix\n");
    }
   
    // 9. symmetric matrix check
    printf("9. SYMMETRIC MATRIX: ");
    int is_symmetric = 0;
    if (is_square) {
        is_symmetric = 1;
        for (Erow = 0; Erow < rows && is_symmetric; Erow++) {
            for (Ecol = 0; Ecol < cols && is_symmetric; Ecol++) {
                if (matrix[Erow][Ecol] != matrix[Ecol][Erow]) {
                    is_symmetric = 0;
                }
            }
        }
        printf("%s (matrix equals its transpose)\n", is_symmetric ? "YES" : "NO");
    } else {
        printf("NO (not a square matrix)\n");
    }
   
    // 10. skew-symmetric matrix check
    printf("10. SKEW-SYMMETRIC MATRIX: ");
    int is_skew_symmetric = 0;
    if (is_square) {
        is_skew_symmetric = 1;
        for (Erow = 0; Erow < rows && is_skew_symmetric; Erow++) {
            for (Ecol = 0; Ecol < cols && is_skew_symmetric; Ecol++) {
                if (matrix[Erow][Ecol] != -matrix[Ecol][Erow]) {
                    is_skew_symmetric = 0;
                }
            }
        }
        printf("%s (matrix equals negative of its transpose)\n", is_skew_symmetric ? "YES" : "NO");
    } else {
        printf("NO (not a square matrix)\n");
    }
   
    // 11. singular/non-singular check
    printf("11. SINGULAR/NON-SINGULAR: ");
    if (is_square && (rows == 2 || rows == 3)) {
        int determinant = 0;
       
        if (rows == 2) {
            determinant = matrix[0][0] * matrix[1][1] - matrix[0][1] * matrix[1][0];
        } else if (rows == 3) {
           
            determinant = matrix[0][0] * (matrix[1][1] * matrix[2][2] - matrix[1][2] * matrix[2][1])
                        - matrix[0][1] * (matrix[1][0] * matrix[2][2] - matrix[1][2] * matrix[2][0])
                        + matrix[0][2] * (matrix[1][0] * matrix[2][1] - matrix[1][1] * matrix[2][0]);
        }
       
        printf("%s (determinant = %d)\n",
               (determinant == 0) ? "SINGULAR" : "NON-SINGULAR",
               determinant);
    } else {
        printf("Cannot determine\n");
    }
   
    // 12. equal matrix check
    printf("12. EQUAL MATRIX CHECK: ");
    char check_equal;
    printf("Do you want to compare with another matrix? (y/n): ");
    scanf(" %c", &check_equal);


    if (check_equal == 'y' || check_equal == 'Y') {
        int second_matrix[5][5];
        int second_rows, second_cols;
       
        printf("enter dimensions of second matrix:\n");
        printf("rows: ");
        scanf("%d", &second_rows);
        printf("columns: ");
        scanf("%d", &second_cols);
       
        if (second_rows == rows && second_cols == cols) {
            printf("enter second matrix elements:\n");
            for (Erow = 0; Erow < second_rows; Erow++) {
                for (Ecol = 0; Ecol < second_cols; Ecol++) {
                    printf("enter element [%d][%d]: ", Erow + 1, Ecol + 1);
                    scanf("%d", &second_matrix[Erow][Ecol]);
                }
            }
           
            int matrices_equal = 1;
            for (Erow = 0; Erow < rows && matrices_equal; Erow++) {
                for (Ecol = 0; Ecol < cols && matrices_equal; Ecol++) {
                    if (matrix[Erow][Ecol] != second_matrix[Erow][Ecol]) {
                        matrices_equal = 0;
                    }
                }
            }
           
            printf("matrices are %s\n", matrices_equal ? "EQUAL" : "NOT EQUAL");
        } else {
            printf("NO:different dimensions\n");
        }
    } else {
        printf("skipped\n");
    }
   
    // 13. row matrix check
    printf("13. row matrix check: ");
    printf("%s (%dx%d matrix)\n",
           (rows == 1) ? "YES" : "NO", rows, cols);
   
    // 14. column matrix check
    printf("14. column matrix check: ");
    printf("%s (%dx%d matrix)\n",
           (cols == 1) ? "YES" : "NO", rows, cols);
   
    // 15. NNll Matrix
    printf("15. NULL MATRIX: ");
    printf("%s (same as zero matrix)\n", is_zero ? "YES" : "NO");
   
    // 16. idempotent matrix check
    printf("16. IDEMPOTENT MATRIX: ");
    if (is_square && rows <= 3) {  
       
        for (Erow = 0; Erow < rows; Erow++) {
            for (Ecol = 0; Ecol < cols; Ecol++) {
                matrix_square[Erow][Ecol] = 0;
                for (int multiply_index = 0; multiply_index < rows; multiply_index++) {
                    matrix_square[Erow][Ecol] +=
                        matrix[Erow][multiply_index] * matrix[multiply_index][Ecol];
                }
            }
        }
       
       
        int is_idempotent = 1;
        for (Erow = 0; Erow < rows && is_idempotent; Erow++) {
            for (Ecol = 0; Ecol < cols && is_idempotent; Ecol++) {
                if (matrix_square[Erow][Ecol] != matrix[Erow][Ecol]) {
                    is_idempotent = 0;
                }
            }
        }
       
        printf("%s (A^2 %s A)\n",
               is_idempotent ? "YES" : "NO",
               is_idempotent ? "equals" : "does not equal");
    } else {
        printf("Cannot determine:matrix too large or not square.\n");
    }
   
    // 17. nilpotent matrix check
    printf("17. NILPOTENT MATRIX: ");
    if (is_square && rows <= 3) {
       
        int is_nilpotent = 1;
        for (Erow = 0; Erow < rows && is_nilpotent; Erow++) {
            for (Ecol = 0; Ecol < cols && is_nilpotent; Ecol++) {
                if (matrix_square[Erow][Ecol] != 0) {
                    is_nilpotent = 0;
                }
            }
        }
       
        printf("%s (A^2 %s zero matrix)\n",
               is_nilpotent ? "YES" : "NO",
               is_nilpotent ? "equals" : "does not equal");
    } else {
        printf("Cannot determine\n");
    }
   
   


   
    // count and list all applicable types
    int type_count = 0;
    printf("\nMatrix Types Found:\n");


    if (is_square) {
        printf("Square Matrix\n");
        type_count++;
    }


    if (!is_square) {
        printf("Rectangular Matrix\n");
        type_count++;
    }


    if (rows == 1) {
        printf("Row Matrix\n");
        type_count++;
    }


    if (cols == 1) {
        printf("Column Matrix\n");
        type_count++;
    }


    if (is_zero) {
        printf("Zero/Null Matrix\n");
        type_count++;
    }


    if (is_identity) {
        printf("Identity Matrix\n");
        type_count++;
    }


    if (is_diagonal) {
        printf("Diagonal Matrix\n");
        type_count++;
    }


    if (is_scalar) {
        printf("Scalar Matrix\n");
        type_count++;
    }


    if (is_upper_triangular) {
        printf("Upper Triangular Matrix\n");
        type_count++;
    }


    if (is_lower_triangular) {
        printf("Lower Triangular Matrix\n");
        type_count++;
    }


    if (is_symmetric) {
        printf("Symmetric Matrix\n");
        type_count++;
    }


    if (is_skew_symmetric) {
        printf("skew symmetric Matrix\n");
        type_count++;
    }


   
    if (is_square && rows <= 3) {
       
        int is_idempotent = 1;
        for (Erow = 0; Erow < rows && is_idempotent; Erow++) {
            for (Ecol = 0; Ecol < cols && is_idempotent; Ecol++) {
                if (matrix_square[Erow][Ecol] != matrix[Erow][Ecol]) {
                    is_idempotent = 0;
                }
            }
        }
       
        if (is_idempotent) {
            printf("idempotent matrix\n");
            type_count++;
        }
       
        // Check nilpotent result
        int is_nilpotent = 1;
        for (Erow = 0; Erow < rows && is_nilpotent; Erow++) {
            for (Ecol = 0; Ecol < cols && is_nilpotent; Ecol++) {
                if (matrix_square[Erow][Ecol] != 0) {
                    is_nilpotent = 0;
                }
            }
        }
       
        if (is_nilpotent) {
            printf("Nilpotent matrix\n");
            type_count++;
        }
    }


    printf("\ntotal types found: %d\n", type_count);


   
    return 0;




}