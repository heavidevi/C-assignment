#include<stdio.h>
#include <string.h>
int main(){
    int num;
    while(num%2==0&&num>0){
        printf("enter odd positive number");
        scanf("%i",&num);
    }
    int half=num/2;
    int start=half-1;
    int last=half+1;


    for(int i=0;i<half;i++){
        for(int i=0;i<num;i++){
            if((i>start)&&(i<last)){
                printf("*");
            }else{
                printf(" ");
            }

        }
        start--;
        last++;
        printf("\n");
    }
    start=-1;
    last=num;
    for (int i=0;i<=half;i++){
        for(int i=0;i<num;i++){
            if((i>start)&&(i<last)){
                printf("*");
            }else{
                printf(" ");
            }
        }
        start++;
        last--;
        printf("\n");
    }
    return 0;

}
