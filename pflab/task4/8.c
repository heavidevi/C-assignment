#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main(){
    int num1,num2;
    char *operator=malloc(sizeof(char));
    printf("enter num1 and num2");
    scanf("%i %i",&num1,&num2);
    printf("enter operator \n + for addition \n - for subtraction \n * for multiplication \n / for division \n %% for modulus \n ^ for exponentiation\n");
    scanf("%s",operator);

    switch (*operator){
        case '+':
            printf("%i",num1+num2);
            break;
        case '-':
            printf("%i",num1-num2);
            break;
        case '*':
            printf("%i",num1*num2);
            break;
        case '/':
            if (num2 == 0) {
                printf("Error: Division by zero");
            } else {
                printf("%.2f",(float)num1/num2);
                break;
            }
            break;
        case '%':
            if (num2 == 0) {
                printf("Error: modulus by zero");
            } else {
                printf("%i",num1%num2);
                break;
            }
            break;
        case '^':
            printf("%.1f",pow(num1,num2));
            break;

        default:
            printf("Invalid Input");
            break;
        }


    free(operator);
    return 0;
};
