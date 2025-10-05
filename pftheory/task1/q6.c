#include <stdio.h>

int main() {
    int i, j, k;
    
    // Get input values
    printf("Enter three integers (i j k): ");
    scanf("%d %d %d", &i, &j, &k);
    
    printf("\n=== DRY RUN TRACE ===\n");
    printf("Initial values: i=%d, j=%d, k=%d\n", i, j, k);
    
    printf("Checking condition: i < j (%d < %d)\n", i, j);
    
    if (i < j) {
        printf("Condition i < j is TRUE\n");
        printf("Checking nested condition: j < k (%d < %d)\n", j, k);
        
        if (j < k) {
            printf("Condition j < k is TRUE\n");
            printf("Executing: i = j (i = %d)\n", j);
            i = j;
            printf("After assignment: i=%d, j=%d, k=%d\n", i, j, k);
        } else {
            printf("Condition j < k is FALSE\n");
            printf("No action taken in nested if\n");
        }
    }
    else {
        printf("Condition i < j is FALSE\n");
        printf("Executing: j = k (j = %d)\n", k);
        j = k;
        printf("After j = k: i=%d, j=%d, k=%d\n", i, j, k);
        
        printf("Checking condition: j > k (%d > %d)\n", j, k);
        
        if (j > k) {
            printf("Condition j > k is TRUE\n");
            printf("Executing: j = i (j = %d)\n", i);
            j = i;
            printf("After j = i: i=%d, j=%d, k=%d\n", i, j, k);
        }
        else {
            printf("Condition j > k is FALSE\n");
            printf("Executing: i = k (i = %d)\n", k);
            i = k;
            printf("After i = k: i=%d, j=%d, k=%d\n", i, j, k);
        }
    }
    
    printf("\n=== FINAL RESULT ===\n");
    printf("Final values: %d %d %d\n", i, j, k);
    
    return 0;
}



