#include<stdio.h>
#include<math.h>

int main(){
    int num;
    printf("enter number");
    scanf("%i",&num);
    int half=num/2;
    int start=num-1;
    int end=num+1;
    for(int i=0;i<num;i++){
        int count=1;
        for(int j=0;j<num*2;j++){
            if(j>start&&j<end){
                printf("%i",count);
                if(j<num){
                    count++;
                }else{
                    count--;
                }
            }else{
                printf(" ");
            }
        }
        printf("\n");
        start--;
        end++;
    }
}
