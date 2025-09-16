#include <stdio.h>

int main(){
    int a,b,c;
    printf("Enter three side of traingle: ");
    scanf("%d %d %d",&a,&b,&c);
    if(a+b>c && b+c>a && c+a>b){
        if (a==b && b==c){
            printf("Equilateral triangle\n");
        }
        else if (a==b || b==c || c==a){
            printf("Isosceles triangle\n");
        }
        else{
            printf("Scalene triangle\n");
        }
    }
    else{
        printf("Invalid triangle\n");
    }
    return 0;
}