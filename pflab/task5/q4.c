#include <stdio.h>

int main(){
    int *shape;
    int *property;
    printf("Enter shape :\n1.circle\n2.square\n3.rectangle): ");
    scanf("%i", shape);
   

    switch (*shape)
    {
    case 1:
        printf("You selected circle\n");
        printf("Enter property :\n1.area\n2.circumference): ");
        scanf("%i", property);
        switch (*property)
        {
        case 1:
            printf("You selected area\n");
            break;

        case 2:
            printf("You selected circumference\n");
            break;

        default:
            break;
        }
        break;

    case 2:
        printf("You selected square\n");
        printf("Enter property :\n1.area\n2.perimeter): ");
        scanf("%i", property);
        switch (*property)
        {
        case 1:
            printf("You selected area\n");
            break;

        case 2:
            printf("You selected perimeter\n");
            break;

        default:
            break;
        }
        break;

    case 3:
        printf("You selected rectangle\n");
        printf("Enter property :\n1.area\n2.perimeter): ");
        scanf("%i", property);
        switch (*property)
        {
        case 1:
            printf("You selected area\n");
            break;

        case 2:
            printf("You selected perimeter\n");
            break;

        default:
            break;
        }
        break;

    default:
        printf("Invalid shape\n");
        break;
    }
    return 0;
}