#include<stdio.h>

int main(){
    int arr[10];
    int max=-99999999;
    int min=999999;
    for (int i = 0; i <10; i++)
    {
        printf("enter a number");
        scanf("%i",&arr[i]);
        if (arr[i]>max)
        {
            max=arr[i];
        }else if(arr[i]<min){
            min=arr[i];
        }
      
    }
    printf("difference %i\n", max-min);
}