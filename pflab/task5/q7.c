#include <stdio.h>

int main(){
    int num;
    printf("Enter an integer: ");
    scanf("%d", &num);
    (num>0)?(num%2==0?printf("Positive even number\n"):printf("Positive odd number\n")):((num<0)?((num%3==0)?printf("divisible by three and negative\n"):printf("not divisible by three but negative\n")):printf("Zero\n"));

    return 0;
}