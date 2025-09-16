#include <stdio.h>
#include <stdlib.h>

int main(){
    int *num=malloc(sizeof(int));
    printf("enter num");
    scanf("%i",num);
    if(*num>0){
        printf("postive");
    }else if(*num<0)
    {
        printf("negative");
    }else{
        printf("equal to zero");
    }
    return 0;
    free(num);
}