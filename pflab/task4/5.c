#include <stdio.h>

int main(){
    float grade;
    printf("enter grade");
    scanf("%f",&grade);
    if (grade>0){
        if(grade<40){
            printf("F");
        }else if(grade<54){
            printf("D");
        }else if(grade<69){
            printf("C");
        }else if(grade<84){
            printf("B");
        }else if (grade<=100){
            printf("A");
        }
    }else {
        printf("invalid grade");
    }
    return 0;
}