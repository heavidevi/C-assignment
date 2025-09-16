#include <stdio.h>

int main(){
    int mark1,mark2,mark3;
    printf("Enter marks of three subjects: ");
    scanf("%i %i %i",&mark1,&mark2,&mark3);
    float avg = (mark1 + mark2 + mark3)/3.0;
    if (mark1>0&&mark1<=100 && mark2>0&&mark2<=100 && mark3>0&&mark3<=100){
        if(avg>=80){
            printf("Pass with distinction\n");
        
        }else if(avg>=60){
            printf("Pass with merit\n");
        }else if(mark1>40&&mark2>40&&mark3>40){
           printf("Pass\n");
        }else{
            printf("Fail\n");
        }
    }
    else{
        printf("Invalid marks\n");
    }
    return 0;
}