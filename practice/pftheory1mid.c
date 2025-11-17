#include<stdio.h>
#include<math.h>

int nominal = 7400;      // 74.00 * 100 = 7400
int tolerance = 5;       // 0.05 * 100 = 5

int firstdetectindex(float *arr, int len){
    int count = 0;
    int is_defect = 0;
    int sub;
    int arr_scaled;
    
    while(is_defect == 0 && count < len){
        // Convert float to integer by multiplying by 100
        arr_scaled = (int)(*arr * 100 + 0.5); // +0.5 for proper rounding
        
        sub = nominal - arr_scaled;
        if(sub < 0) sub = -sub; // Get absolute value
        
        printf("Index %d: Value=%.2f, Scaled=%d, Diff=%d\n", count, *arr, arr_scaled, sub);
        
        if(sub > tolerance){
            printf("Defect found at index %d\n", count);
            return count;
        }
        count++;
        arr++;
    }
    return -1;
}

int main(){
    float batchMeasurements[] = {74.02, 73.99, 74.01, 74.05, 73.98, 74.08, 73.95, 74.00, 73.90, 74.03};
    int batchsize = 10;
    float *ptr = batchMeasurements;  
    int index = firstdetectindex(ptr, batchsize);
    printf("the first defect is at: %i\n", index);
    return 0;
}
