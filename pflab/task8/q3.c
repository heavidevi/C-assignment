#include <stdio.h>


int main() {
   
    int Fmatrix[3][3];
    int Smatrix[3][3];
    int result_matrix[3][3];
   
    int first_rows, first_cols;
    int second_rows, second_cols;
    int Erow, Ecol, multiply_index;  
   
    
   
   
    printf("enter dimensions of first matrix:\n");
    printf("rows (max 3): ");
    scanf("%d", &first_rows);
    printf("columns (max 3): ");
    scanf("%d", &first_cols);
   
    // validate first matrix dimensions
    if (first_rows > 3 || first_cols > 3 || first_rows < 1 || first_cols < 1) {
        printf("invalid dimensions for first matrix\n");
        return 1;
    }


   
    printf("enter dimensions of second matrix:\n");
    printf("rows (max 3) ");
    scanf("%d", &second_rows);
    printf("columns (max 3): ");
    scanf("%d", &second_cols);
   
    // validate second matrix dimensions
    if (second_rows > 3 || second_cols > 3 || second_rows < 1 || second_cols < 1) {
        printf("invalid dimensions for second matrix\n");
        return 1;
    }
   
    //if multiplication is possible
    if (first_cols != second_rows) {
        printf("matrix multiplication not possible\n");
        printf("columns of first matrix (%d) must equal rows of second matrix (%d)\n",
               first_cols, second_rows);
        return 1;
    }
   
    printf("multiplication is possible: result will be %dx%d\n", first_rows, second_cols);
   
    // elements for first matrix
    printf("\nenter elements of first matrix:\n");
    for (Erow = 0; Erow < first_rows; Erow++) {
        for (Ecol = 0; Ecol < first_cols; Ecol++) {
            printf("element [%d][%d]: ", Erow + 1, Ecol + 1);
            scanf("%d", &Fmatrix[Erow][Ecol]);
        }
    }
   
    // elements for second matrix
    printf("enter elements of second matrix:\n");
    for (Erow = 0; Erow < second_rows; Erow++) {
        for (Ecol = 0; Ecol < second_cols; Ecol++) {
            printf("element [%d][%d]: ", Erow + 1, Ecol + 1);
            scanf("%d", &Smatrix[Erow][Ecol]);
        }
    }
   
    //first matrix
    printf("\nfirst matrix (%dx%d)\n", first_rows, first_cols);
    for (Erow = 0; Erow < first_rows; Erow++) {
        printf("| ");
        for (Ecol = 0; Ecol < first_cols; Ecol++) {
            printf("%4d ", Fmatrix[Erow][Ecol]);
        }
        printf("|\n");
    }
   
    //second matrix
    printf("\nsecond matrix (%dx%d)\n", second_rows, second_cols);
    for (Erow = 0; Erow < second_rows; Erow++) {
        printf("| ");
        for (Ecol = 0; Ecol < second_cols; Ecol++) {
            printf("%4d ", Smatrix[Erow][Ecol]);
        }
        printf("|\n");
    }
   
    // matrix multiplication


   
   
    for (Erow = 0; Erow < first_rows; Erow++) {
       
        for (Ecol = 0; Ecol < second_cols; Ecol++) {
           
       
            result_matrix[Erow][Ecol] = 0;
          
           
         
            for (multiply_index = 0; multiply_index < first_cols; multiply_index++) {
               
         
                int product = Fmatrix[Erow][multiply_index] *
                             Smatrix[multiply_index][Ecol];
               
                result_matrix[Erow][Ecol] += product;
               
                              
               
                
            }
           
            printf(" = %d\n", result_matrix[Erow][Ecol]);
        }
        printf("\n");
    }
   
    //result
    printf("result matrix (%dx%d)\n", first_rows, second_cols);
    for (Erow = 0; Erow < first_rows; Erow++) {
        printf("| ");
        for (Ecol = 0; Ecol < second_cols; Ecol++) {
            printf("%4d ", result_matrix[Erow][Ecol]);
        }
        printf("|\n");
    }
   
   
    return 0;
}
