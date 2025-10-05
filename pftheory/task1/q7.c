#include <stdio.h>

int main()
{
    int value;
    printf("Please enter a value in the range 1...7 (1 =Monday and 7=Sunday): ");
    scanf("%d", &value);

    switch (value)
    {
        case 1:
            printf("You entered a one\n");
            printf(" Day is Monday");
            break;
        
        case 2:
            printf("You entered a two\n");
            printf(" Day is Tuesday");
            break;
        
        case 3:
            printf("You entered a three\n");
            printf(" Day is Wednesday");
            break;
        
        case 4:
            printf("You entered a four\n");
            printf(" Day is Thursday");
            break;
        
        case 5:
            printf("You entered a five\n");
            printf(" Day is Friday");
            break;
        
        case 6:
            printf("You entered a six\n");
            printf(" Day is Saturday");
            break;
        
        case 7:
            printf("You entered a seven\n");
            printf("Day is Sunday");
            break;
        
        default:
            printf("You entered a value out of range\n");
            break;
    }
    
    return 0;
}
