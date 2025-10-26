#include<stdio.h>
#include<string.h>

int main(){

    char str[100];
    printf("Enter string: ");
    scanf("%[^A-Za-z]", str);

    printf("Non-alphabetic string: %s\n", str);
    return 0;
}
