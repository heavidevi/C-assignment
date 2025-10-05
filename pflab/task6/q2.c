#include<stdio.h>
int main(){
    int num=0;
    int sum=0;
    int numarray[5];
    while (num<10000||num>99999){
        printf("enter 5 digits number \n");
        scanf("%d",&num);
    }
    int original=num;
    int j=10000;
    int ch=num;
    for(int i=0;i<5;i++){
        ch=num/j;
        num=num%j;
        numarray[i]=ch;
        sum+=ch;

        j=j/10;


    }
    printf("sum:%i\n",sum);

    if(sum%2==0){
        int count=0;
        for(int i=2;i<original;i++){
            if(original%i==0){
                count++;

            }
        }
        (count>1)?printf("number is prime and "):printf("number is not prime but ");
        printf("sum is even\n");
    }else{
        if((numarray[0]==numarray[4])&&(numarray[1]==numarray[3])){
            printf("number is palindrome");
        }
        printf("sum is odd\n");
    }
    return 0;
}
