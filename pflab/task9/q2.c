#include <stdio.h>

int main(){
    int nums[10] = {10, 20, 30, 40, 50, 60, 70, 80, 90, 100};
    int *ptr = nums;
    
    printf("Array traversal using pointer arithmetic:\n");
    
    for(int i = 0; i < 10; i++){
        printf("Element %d: Address = %p, Value = %d\n", i+1, ptr, *ptr);
        ptr++;
    }
    
    ptr = nums;
    printf("\nAddress and value differences:\n");
    
    for(int i = 0; i < 9; i++){
        int *next = ptr + 1;
        printf("Between element %d and %d:\n", i+1, i+2);
        printf("Address difference: %ld bytes\n", (char*)next - (char*)ptr);
        printf("Value difference: %d\n", *next - *ptr);
        ptr++;
    }
    
    return 0;
}