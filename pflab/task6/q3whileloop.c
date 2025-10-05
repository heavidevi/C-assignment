#include<stdio.h>
#include<string.h>

int main() {
    int num = 0;


    while (num % 2 == 0 || num <= 0) {
        printf("Enter odd positive number: ");
        scanf("%d", &num);
    }

    int half = num / 2;
    int start = half - 1;
    int last = half + 1;

    
    int row = 0;
    while (row < half) {
        int col = 0;
        while (col < num) {
            if ((col > start) && (col < last)) {
                printf("*");
            } else {
                printf(" ");
            }
            col++;
        }
        start--;
        last++;
        printf("\n");
        row++;
    }

   
    start = -1;
    last = num;
    row = 0;
    while (row <= half) {
        int col = 0;
        while (col < num) {
            if ((col > start) && (col < last)) {
                printf("*");
            } else {
                printf(" ");
            }
            col++;
        }
        start++;
        last--;
        printf("\n");
        row++;
    }

    return 0;
}
