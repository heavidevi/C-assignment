#include <stdio.h>

int main() {
    // 3d matrix 
    int cube_matrix[3][3][3];
    int layer_index, row_index, col_index;
    
    printf("=== 3D MATRIX LAYER SIMILARITY ANALYZER ===\n");
    printf("enter elements for 3x3x3 matrix:\n");
    
    // input
    for (layer_index = 0; layer_index < 3; layer_index++) {
        printf("\n--- entering layer %d ---\n", layer_index + 1);
        for (row_index = 0; row_index < 3; row_index++) {
            for (col_index = 0; col_index < 3; col_index++) {
                printf("element [layer %d][row %d][col %d]: ", 
                       layer_index + 1, row_index + 1, col_index + 1);
                scanf("%d", &cube_matrix[layer_index][row_index][col_index]);
            }
        }
    }
    
    // display 
    printf("\n=== 3D MATRIX DISPLAY ===\n");
    for (layer_index = 0; layer_index < 3; layer_index++) {
        printf("layer %d matrix:\n", layer_index + 1);
        for (row_index = 0; row_index < 3; row_index++) {
            printf("| ");
            for (col_index = 0; col_index < 3; col_index++) {
                printf("%4d ", cube_matrix[layer_index][row_index][col_index]);
            }
            printf("|\n");
        }
        printf("\n");
    }
    
    // difference 
    int differences[100][3]; 
    int difference_count = 0;
    
   
  
    
    // layer 1 with layer 2
    for (row_index = 0; row_index < 3; row_index++) {
        for (col_index = 0; col_index < 3; col_index++) {
            if (cube_matrix[0][row_index][col_index] != cube_matrix[1][row_index][col_index]) {
                differences[difference_count][0] = row_index;     
                differences[difference_count][1] = col_index;       
                differences[difference_count][2] = 1;            
                difference_count++;
            }
        }
    }
    
  
    for (row_index = 0; row_index < 3; row_index++) {
        for (col_index = 0; col_index < 3; col_index++) {
            if (cube_matrix[0][row_index][col_index] != cube_matrix[2][row_index][col_index]) {
                differences[difference_count][0] = row_index;    
                differences[difference_count][1] = col_index;     
                differences[difference_count][2] = 2;            
                difference_count++;
            }
        }
    }
    
    // layer 2 with layer 3 
    for (row_index = 0; row_index < 3; row_index++) {
        for (col_index = 0; col_index < 3; col_index++) {
            if (cube_matrix[1][row_index][col_index] != cube_matrix[2][row_index][col_index]) {
                differences[difference_count][0] = row_index;     
                differences[difference_count][1] = col_index;
                differences[difference_count][2] = 3;            
                difference_count++;
            }
        }
    }
    
    // display 
    printf("\n=== DIFFERENCES FOUND ===\n");
    if (difference_count == 0) {
        printf("no differences found - all layers are identical\n");
    } else {
        printf("total differences found: %d\n", difference_count);
        printf("difference positions {x,y,z} format:\n");
        printf("x=row, y=column, z=comparison(1=layer1vs2, 2=layer1vs3, 3=layer2vs3)\n\n");
        
        for (int diff_index = 0; diff_index < difference_count; diff_index++) {
            printf("{%d,%d,%d}\n", 
                   differences[diff_index][0], 
                   differences[diff_index][1], 
                   differences[diff_index][2]);
        }
    }
    
    printf("\n=== SUMMARY ===\n");
    if (difference_count == 0) {
        printf("all layers identical\n");
    } else if (difference_count < 10) {
        printf("layers mostly similar\n");
    } else {
        printf("layers significantly different\n");
    }
    
    
    return 0;
}