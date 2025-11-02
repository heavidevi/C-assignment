#include<stdio.h>
#include<string.h>
#include<stdlib.h>

#define PRODUCT 3
#define MAX_CART_ITEMS 100

int cart_count = 0;
char customer_name[20];
char customer_cnic[15];

int customerinfo(){
    printf("Enter your name: ");
    scanf("%19s", customer_name);
    printf("Enter your CNIC: ");
    scanf("%14s", customer_cnic);
    printf("Customer information saved successfully!\n");
    return 1;
}

int displayTable(int products[4][PRODUCT], char product[][20]){
    printf("\n----- INVENTORY -----\n");
    printf("%-15s %-15s %-15s\n", "Product Code", "Stock Quantity", "Price per Unit");
    printf("-----------------------------------------------\n");
    
    for(int i = 0; i < 4; i++){
        printf("%-15d %-15d %-15d\n", products[i][0], products[i][1], products[i][2]);
    }
    printf("\n");
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
    int code, quantity;
    printf("Enter product code to purchase: ");
    scanf("%d", &code);
    printf("Enter quantity: ");
    scanf("%d", &quantity);
    
    if (updateinventory(products, code, quantity) == 0){
        printf("Could not add item to cart\n");
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
        return 1;
    }
}

int displaybill(int cart[][2], int price[]) {
    char promo[7];
    int is_promo = 0;
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
    scanf("%6s", promo);
    
    if (strcmp(promo, "Eid2025") == 0){
        printf("Promo code applied! You get 25%% off!\n");
        is_promo = 1;
        sum = sum * 0.75;
        printf("Total after discount: %d\n", sum);
    } else {
        printf("Total: %d\n", sum);
    }
    
    return sum;
}

int show_invoice(int cart[][2], int price[]){
    char address[50];
    printf("Enter your address: ");
    scanf("%49s", address);
    
    system("clear");
    printf("\n===== INVOICE =====\n");
    printf("Customer Name: %s\n", customer_name);
    printf("Customer CNIC: %s\n", customer_cnic);
    printf("Customer Address: %s\n", address);
    
    int total = displaybill(cart, price);
    printf("===================\n");
    printf("Thank you for shopping with us!\n");
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

int menuSystem(int products[4][PRODUCT], char product[][15], int cart[][2], int cartprice[]){
    int choice;
    displayMenu();
    scanf("%d", &choice);
    
    switch(choice){
        case 1:
            customerinfo();
            break;
        case 2:
            displayTable(products, product);
            break;
        case 3:
            if(cart_count >= MAX_CART_ITEMS){
                printf("Cart is full!\n");
            } else {
                Additem(products, cart, cartprice);
            }
            break;
        case 4:
            if(cart_count == 0){
                printf("Cart is empty!\n");
            } else {
                displaybill(cart, cartprice);
            }
            break;
        case 5:
            if(cart_count == 0){
                printf("Cart is empty! Add items first.\n");
            } else {
                show_invoice(cart, cartprice);
                return 0; // Exit after generating invoice
            }
            break;
        case 6:
            printf("Thank you for using our system!\n");
            return 0; // Exit
        default:
            printf("Invalid choice! Please try again.\n");
    }
    
    
    return menuSystem(products, product, cart, cartprice);
}

int main(){
    char product[PRODUCT][20] = {"product code", "quantity in stock", "Price per product"};
    int products[4][PRODUCT] = {
        {1, 50, 100},  
        {2, 10, 200},   
        {3, 20, 300},  
        {4, 8, 150}     
    };
    
    int cart[MAX_CART_ITEMS][2] = {{0,0}};
    int cartprice[MAX_CART_ITEMS] = {0};
    
    printf("Welcome to Supermarket Management System!\n");
    

    menuSystem(products, product, cart, cartprice);
    
    printf("System terminated successfully!\n");
    return 0;
}