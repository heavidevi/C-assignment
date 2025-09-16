#include <stdio.h>

int main() {
    int level;
    printf("Enter your level: ");
    scanf("%d", &level);
    if (level>6){
        printf("Evacuation Required");
        
    }else if (level>4){
        printf("Medium Relief Package");

    }else if (level>2){
        printf("Small Relief Package");
    }else if (level>=0){
        printf("No Relief Required");
    }

    return 0;
}