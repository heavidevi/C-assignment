#include<stdio.h>
#include<string.h>
#include<stdlib.h>

#define PRODUCT 3
#define MAX_CART_ITEMS 100

int cart_count = 0;
char customer_name[20];
char customer_cnic[15];

void clearscreen() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

int customerinfo(){
    printf("Enter your name: ");
    scanf("%19s", customer_name);
    printf("Enter your CNIC: ");
    scanf("%14s", customer_cnic);
    printf("Customer information saved successfully!\n");
    
    printf("\nPress Enter to continue...");
    while(getchar() != '\n'); 
    getchar(); 
    return 1;
}

int displayTable(int products[4][PRODUCT]){
    printf("\n----- INVENTORY -----\n");
    printf("%-15s %-15s %-15s\n", "Product Code", "Stock Quantity", "Price per Unit");
    printf("-----------------------------------------------\n");
    
    for(int i = 0; i < 4; i++){
        printf("%-15d %-15d %-15d\n", products[i][0], products[i][1], products[i][2]);
    }
    printf("\n");
    
    printf("\nPress Enter to continue...");
    while(getchar() != '\n'); 
    getchar(); 
    return 1;
}

int updateinventory(int products[4][PRODUCT], int code, int quantity){
    for(int i = 0; i < 4; i++){
        if(products[i][0] == code){
            if(products[i][1] >= quantity){
                products[i][1] -= quantity;
                printf("Purchase successful! Stock updated.\n");
                return 1;
            }
            else{
                printf("Insufficient stock! Available: %d\n", products[i][1]);
                return 0;
            }
        }
    }
    printf("Product code not found!\n");
    return 0;
}

int Additem(int products[4][PRODUCT], int cart[][2], int price[]){
    if(cart_count >= MAX_CART_ITEMS){
        printf("Cart is full!\n");
        printf("\nPress Enter to continue...");
        while(getchar() != '\n'); 
        getchar(); 
        return 0;
    }
    
    int code, quantity;
    printf("Enter product code to purchase: ");
    scanf("%d", &code);
    printf("Enter quantity: ");
    scanf("%d", &quantity);
    
    if (updateinventory(products, code, quantity) == 0){
        printf("Could not add item to cart\n");
        printf("\nPress Enter to continue...");
        while(getchar() != '\n'); 
        getchar(); 
        return 0;
    } else {
        printf("Item added to cart successfully!\n");
        cart[cart_count][0] = code;
        cart[cart_count][1] = quantity;
        
        for(int i = 0; i < 4; i++){
            if(products[i][0] == code){
                price[cart_count] = quantity * products[i][2];
                break;
            }
        }
        cart_count++;
        printf("\nPress Enter to continue...");
        while(getchar() != '\n'); 
        getchar(); 
        return 1;
    }
}

int displaybill(int cart[][2], int price[]) {
    if(cart_count == 0){
        printf("Cart is empty!\n");
        printf("\nPress Enter to continue...");
        while(getchar() != '\n'); 
        getchar(); 
        return 0;
    }
    
    char promo[10];
    int sum = 0;
    
    printf("\n----- BILL DETAILS -----\n");
    printf("%-15s %-10s %-10s\n", "Product Code", "Quantity", "Price");
    printf("---------------------------------------\n");
    
    for(int i = 0; i < cart_count; i++){
        printf("%-15d %-10d %-10d\n", cart[i][0], cart[i][1], price[i]);
        sum += price[i];
    }
    
    printf("---------------------------------------\n");
    printf("Subtotal: %d\n", sum);
    
    printf("Do you have any promo code? (enter 'no' if none): ");
    scanf("%9s", promo);
    
    if (strcmp(promo, "Eid2025") == 0){
        printf("Promo code applied! You get 25%% off!\n");
        sum = sum * 0.75;
        printf("Total after discount: %d\n", sum);
    } else {
        printf("Total: %d\n", sum);
    }
    
    printf("\nPress Enter to continue...");
    while(getchar() != '\n'); 
    getchar(); 
    return sum;
}

int show_invoice(int cart[][2], int price[]){
    if(cart_count == 0){
        printf("Cart is empty! Add items first.\n");
        printf("\nPress Enter to continue...");
        while(getchar() != '\n'); 
        getchar(); 
        return 0;
    }
    
    char address[50];
    printf("Enter your address: ");
    scanf("%49s", address);
    
    clearscreen();
    printf("\n===== INVOICE =====\n");
    printf("Customer Name: %s\n", customer_name);
    printf("Customer CNIC: %s\n", customer_cnic);
    printf("Customer Address: %s\n", address);
    
    char promo[10];
    int sum = 0;
    
    printf("\n----- FINAL BILL -----\n");
    printf("%-15s %-10s %-10s\n", "Product Code", "Quantity", "Price");
    printf("---------------------------------------\n");
    
    for(int i = 0; i < cart_count; i++){
        printf("%-15d %-10d %-10d\n", cart[i][0], cart[i][1], price[i]);
        sum += price[i];
    }
    
    printf("---------------------------------------\n");
    printf("Subtotal: %d\n", sum);
    
    printf("Enter promo code (or 'no'): ");
    scanf("%9s", promo);
    
    if (strcmp(promo, "Eid2025") == 0){
        printf("Promo code applied! 25%% discount!\n");
        sum = sum * 0.75;
        printf("Final Total: %d\n", sum);
    } else {
        printf("Final Total: %d\n", sum);
    }
    
    printf("===================\n");
    printf("Thank you for shopping with us!\n");
    printf("\nPress Enter to continue...");
    while(getchar() != '\n'); 
    getchar(); 
    return 1;
}

void displayMenu(){
    printf("\n===== SUPERMARKET MANAGEMENT SYSTEM =====\n");
    printf("1. Customer Information\n");
    printf("2. Display Inventory\n");
    printf("3. Add Item to Cart\n");
    printf("4. Display Total Bill\n");
    printf("5. Show Invoice\n");
    printf("6. Exit System\n");
    printf("Enter your choice: ");
}

int main(){
    int products[4][PRODUCT] = {
        {1, 50, 100},  
        {2, 10, 200},   
        {3, 20, 300},  
        {4, 8, 150}     
    };
    
    int cart[MAX_CART_ITEMS][2] = {{0,0}};
    int cartprice[MAX_CART_ITEMS] = {0};
    
    printf("Welcome to Supermarket Management System!\n");
    printf("\nPress Enter to continue...");
    while(getchar() != '\n'); 
    getchar(); 
    
    int choice;
    do {
        clearscreen();
        displayMenu();
        scanf("%d", &choice);
        clearscreen();
        
        switch(choice){
            case 1:
                printf("=== CUSTOMER INFORMATION ===\n");
                customerinfo();
                break;
            case 2:
                printf("=== INVENTORY DISPLAY ===\n");
                displayTable(products);
                break;
            case 3:
                printf("=== ADD ITEM TO CART ===\n");
                Additem(products, cart, cartprice);
                break;
            case 4:
                printf("=== DISPLAY BILL ===\n");
                displaybill(cart, cartprice);
                break;
            case 5:
                printf("=== GENERATE INVOICE ===\n");
                show_invoice(cart, cartprice);
                choice = 6; 
                break;
            case 6:
                printf("Thank you for using our system!\n");
                break;
            default:
                printf("Invalid choice! Please try again.\n");
                printf("\nPress Enter to continue...");
                while(getchar() != '\n'); 
                getchar(); 
        }
        
    } while(choice != 6);
    
    printf("System terminated successfully!\n");
    return 0;
}