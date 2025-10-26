#include<stdio.h>

int main(){
    int array[5]={1,2,3,4,5};
    int temp=array[4];

    for (int i = 4; i>=0; i--)
    {
         array[i]=array[i-1];
    }
    array[0]=temp;
    for (int i = 0; i < 5; i++)
    {
       printf("%i",array[i]);
    }
    printf("\n");


}
