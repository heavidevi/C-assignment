#include<stdio.h>



void initailize(int arr[4][4]){
    int count=0;
    for(int i=0;i<4;i++){
        for(int j=0;j<4;j++){
            arr[i][j]=count+1;
            count++;
        }
    }
}

int even(int *ptr){
    int sum=0;
    for(int i=0;i<4;i++){
        sum+=ptr[i];
    }
    return sum;
}

int odd(int *ptr){
    int sum=0;
    for(int i=3;i>-1;i--){
        sum+=ptr[i];
    }
    return sum;
}

int main(){
    int arr[4][4];
    initailize(arr);
    int sum=0;

    for(int i=0;i<4;i++){
        if(i%2==0){
            sum+=even(arr[i]);
        }else{
            sum+=odd(arr[i]);
        }
    }
    printf("sum:%i",sum);
}
