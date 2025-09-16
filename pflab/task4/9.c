#include <stdio.h>

int main(){
    int rainfall,riverFlow;
    printf("enter rainfall and river flow");
    scanf("%i %i",&rainfall,&riverFlow);
    if (rainfall>0 && riverFlow>0){
        if (rainfall<50 && riverFlow<200){
            printf("Low Risk");
        }else if (rainfall<100 && riverFlow<500){
                printf("Moderate Risk");
        }else if (rainfall<150 && riverFlow<800){
                printf("High Risk");
        }else{
                printf("Severe Risk - Evacuate!");
        }
    }else{
        printf("Invalid Input");
    }
    return 0;
}