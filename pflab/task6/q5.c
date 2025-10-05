#include <stdio.h>

int main() {
    int num;
    printf("Enter number of rows: ");
    scanf("%d", &num);
    if (num >= 1) {
        printf("1\n");
    }
    if (num > 1) {
        int first=1,second=1,next;

        for (int i=2;i<= num;i++) {

            if (i == 2) {
                first = 1;
                second = 1;
                printf("1 1\n");
            } else {
                for (int j = 1; j <= i; j++) {
                    next = first + second;
                    printf("%i ", next);
                    first = second;
                    second = next;
                }
                printf("\n");
            }
        }
    }

    return 0;
}
