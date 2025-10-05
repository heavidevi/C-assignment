#include <stdio.h>

int main() {
    int number, temp, divisor = 1, count = 0;
    printf("Enter a number: ");
    scanf("%d", &number);
    temp = number;
    
    if (temp > 0) {
        do {
            count++;
            temp /= 10;
        } while (temp > 0);
    }
    
    int pos = 1;
    if (pos < count) {
        do {
            divisor *= 10;
            pos++;
        } while (pos < count);
    }
    
    pos = 1;
    if (pos <= count) {
        do {
            int digit = number / divisor;
            printf("Digit %d: %d\n", pos, digit);
            number %= divisor;
            divisor /= 10;
            pos++;
        } while (pos <= count);
    }
    
    return 0;
}
