#include <stdio.h>
#include <stdlib.h>

int main(){
    int num1,num2;
    char *operator=malloc(sizeof(char));
    printf("enter num1 and num2");
    scanf("%i %i",&num1,&num2);
    printf("enter operator \n + for addition \n - for subtraction \n * for multiplication \n / for division");
    scanf("%s",operator);
    switch (*operator)
    {
        case '+':
            printf("%i\n",num1+num2);
            break;
        case '-':
            printf("%i\n",num1-num2);
            break;
        case '*':
            printf("%i\n",num1*num2);
            break;
        case '/':
            if (num2 == 0) {
                printf("Error: Division by zero");
            } else {
                printf("%i\n",num1/num2);
                break;
            }
            break;
        default:
            break;
    };

    free(operator);
    return 0;
}