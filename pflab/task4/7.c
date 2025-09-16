#include <stdio.h>

int main(){
    int unit;
    int unitRate;
    printf("enter unit consumed");
    scanf("%i",&unit);
    if (unit>0){  
        if(unit<101){
            unitRate=10;
        }
        else if(unit<301){
            unitRate=15;
        }else if (unit<501){
            unitRate=20;
        }else{
            unitRate=25;
        }
        printf("total bill is %i",unit*unitRate);
    }else{
        printf("invalid unit");
    }
    return 0;
}