#include <stdio.h>
#include <math.h>

int main() {
    int num, temp, rem, len = 0;
    int sum = 0;

    printf("Enter number: ");
    scanf("%d", &num);


    temp = num;
    while (temp > 0) {
        len++;
        temp = temp / 10;
    }


    temp = num;
    while (temp > 0) {
        rem = temp % 10;
        sum += pow(rem, len);
        temp = temp / 10;
    }

    if (sum == num)
        printf("Armstrong number\n");
    else
        printf("Not Armstrong number\n");

    return 0;
}
