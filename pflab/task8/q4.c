#include <stdio.h>


int main() {
    // 3d array
    int data_cube[3][3][3];
    int layer_index, row_index, col_index;  


    printf("enter elements for 3x3x3 cube:\n");
   
    // input elements
    for (layer_index = 0; layer_index < 3; layer_index++) {
        printf("\nlayer %d\n", layer_index + 1);
        for (row_index = 0; row_index < 3; row_index++) {
            for (col_index = 0; col_index < 3; col_index++) {
                printf("enter element [%d][%d][%d]: ", layer_index, row_index, col_index);
                scanf("%d", &data_cube[layer_index][row_index][col_index]);
            }
        }
    }
   
    // display
    printf("\nCOMPLETE 3D ARRAY\n");
    for (layer_index = 0; layer_index < 3; layer_index++) {
        printf("layer %d:\n", layer_index + 1);
        for (row_index = 0; row_index < 3; row_index++) {
            printf("| ");
            for (col_index = 0; col_index < 3; col_index++) {
                printf("%4d ", data_cube[layer_index][row_index][col_index]);
            }
            printf("|\n");
        }
        printf("\n");
    }
   
    printf("LAYER ANALYSIS\n");
   
    int layer_totals[3];
    int overall_sum = 0;
    int overall_max = data_cube[0][0][0];
    int overall_min = data_cube[0][0][0];
   
    // analyze
    for (layer_index = 0; layer_index < 3; layer_index++) {
       
       
        int layer_sum = 0;
        int layer_max = data_cube[layer_index][0][0];
        int layer_min = data_cube[layer_index][0][0];
       
        // process
        for (row_index = 0; row_index < 3; row_index++) {
            for (col_index = 0; col_index < 3; col_index++) {
                int current_element = data_cube[layer_index][row_index][col_index];
               
                layer_sum += current_element;
               
                if (current_element > layer_max) {
                    layer_max = current_element;
                }
                if (current_element < layer_min) {
                    layer_min = current_element;
                }
               
                overall_sum += current_element;
                if (current_element > overall_max) {
                    overall_max = current_element;
                }
                if (current_element < overall_min) {
                    overall_min = current_element;
                }
            }
        }
       
        layer_totals[layer_index] = layer_sum;
       
        // display
        printf("layer %d maximum: %d\n", layer_index + 1, layer_max);
        printf("layer %d minimum: %d\n", layer_index + 1, layer_min);
        printf("layer %d total: %d\n", layer_index + 1, layer_sum);
        printf("layer %d average: %.2f\n", layer_index + 1, (float)layer_sum / 9);
    }
   
    // results
    printf("\narray results\n");
    printf("maximum: %d\n", overall_max);
    printf("minimum: %d\n", overall_min);
    printf("total: %d\n", overall_sum);
    printf("average: %.2f\n", (float)overall_sum / 27);
   
 
   
    return 0;
}
