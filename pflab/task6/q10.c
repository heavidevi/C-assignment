#include<stdio.h>

int main(){
    int num, temp_num;
    int position = 1;
    int sum = 0;
    
    printf("Enter a number: ");
    scanf("%d", &num);
    
    temp_num = num;
    
    while(temp_num > 0){
        int digit = temp_num % 10;
        
        if(position % 2 == 1){
            sum += digit;
        }
        
        temp_num /= 10;
        position++;
    }
    
    printf("Sum of digits in odd positions: %d\n", sum);
    
    return 0;
}
