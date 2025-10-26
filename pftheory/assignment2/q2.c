#include<stdio.h>

#define PRODUCT 3

char *customerinfo(){
    char name[20];
    char cnic[11];
    printf("Enter your name \n Enter your CNIC");
    scanf("%s %s", &name, &cnic);
    return 1;

}

int displayTable(int products[4][PRODUCT], char *product[]){;
   

    for(int i = 0; i < 3; i++)
    {      
       for(int j=0;j<4;j++){
        printf("%-20s",product[i]);
        printf("%-10d",products[j][i]);
       }
        printf("\n");
    }


}

int updateinventory(int products[4][PRODUCT], int code, int quantity){
    for(int i=0;i<4;i++){
        if(products[i][0]==code){
            if(products[i][1]>=quantity){
                products[i][1]-=quantity;
                printf("Purchase successful\n");
                return 1;
            }
            else{
                printf("Insufficient stock\n");
                return 0;
            }
        }
    }
    printf("Product code not found\n");
    return 0;
}


int Additem(int products[4][PRODUCT]){
    int code, quantity;
    printf("Enter product code and quantity to purchase");
    scanf("%d %d", &code, &quantity);
    updateinventory(products, code, quantity);
}

int displaybill(){
    
    return 1;
}

int main(){
    char product[PRODUCT][15]={"product code","quantity in stock","Price per product"};
    int products[4][PRODUCT] = {
            {1, 50, 100},  
            {2, 10, 200},   
            {3, 20, 300},  
            {4, 8, 150}     
    };

 


    int
}