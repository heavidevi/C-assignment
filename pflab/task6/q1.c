#include<stdio.h>
int main(){
    int num;
    printf("enter num\n");
    scanf("%d",&num);
    if(num<0){
        printf("negative\n");
        return 0;
    }
    else{
        long long int factorial=1;
        while(num>0){
            factorial=factorial*num;
            num--;
        }
        printf("%lld\n",factorial);
    }
    return 0;
}
