#include <stdio.h>
#include <stdlib.h>

int numbers[10]={0,0,0,0,0,0,0,0,0,0};

int main (){
	int num;
	printf("Enter a number: ");
    scanf("%d", &num);
    numbers[num]++;

    if (num > 9 || num < 0)
    {   
        printf("Number     NumberOfOccurrences\n");
        for(int i=0;i<10;i++){
            printf("     %d:       %d\n", i, numbers[i]);
        }
        return 0; 
    }
    else{
        printf("%d\n", num);
        main();

    }
    
}