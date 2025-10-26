#include<stdio.h>
#include<stdlib.h>

// Global variables to store all books (defined only once)
int isbns[100];
char titles[100][50];
float prices[100];
int quantities[100];
int bookCount = 0;

// Function to clear screen
void clearscreen() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

int display(){
    int options;
    printf("BOOKSTORE MANAGEMENT SYSTEM \n");
    printf("Options available:\n 1:Add New Book.\n 2:Process a Sale.\n 3:Generate Low-Stock Report.\n 4:Exit\n");
    printf("Enter your choice: ");
    scanf("%d", &options);
    return options;
}

int addbook(){
    int *isbnpointer;
    char *titlepointer;
    float *pricepointer;
    int *quantitypointer;

    isbnpointer = &isbns[bookCount];
    titlepointer = &titles[bookCount][0];
    pricepointer = &prices[bookCount];
    quantitypointer = &quantities[bookCount];

    printf("Enter ISBN, title, price, quantity:\n");
    scanf("%d %s %f %d", isbnpointer, titlepointer, pricepointer, quantitypointer);

    printf("Book added successfully!\n");
    bookCount++;
    return bookCount;
}

int processsale(int isbn, int quantity){
    for (int i = 0; i < bookCount; i++) {
        if (isbns[i] == isbn) {
            if (quantities[i] >= quantity) {
                quantities[i] -= quantity;
                printf("Sale processed: %d copies of '%s' sold.\n", quantity, titles[i]);
                printf("Remaining stock: %d\n", quantities[i]);
            } else {
                printf("Insufficient stock for '%s'. Available: %d\n", titles[i], quantities[i]);
            }
            return 0;
        }
    }
    printf("Book with ISBN %d not found.\n", isbn);
    return -1;
}

void generateLowStockReport(){
    printf("=== LOW STOCK REPORT (Quantity < 5) ===\n");
    int lowStockCount = 0;

    for(int i = 0; i < bookCount; i++){
        if(quantities[i] < 5){
            printf("ISBN: %d, Title: %s, Price: %.2f, Quantity: %d\n",
                   isbns[i], titles[i], prices[i], quantities[i]);
            lowStockCount++;
        }
    }

    if(lowStockCount == 0){
        printf("No books with low stock.\n");
    } else {
        printf("Total books with low stock: %d\n", lowStockCount);
    }
}

int main(){
    int choice;

    do {
        clearscreen();
        choice = display();

        switch (choice) {
            case 1:
                printf("Add New Book selected.\n");
                addbook();
                break;
            case 2:
                printf("Process a Sale selected.\n");
                if(bookCount == 0){
                    printf("No books available in inventory.\n");
                } else {
                    printf("Enter ISBN and quantity sold:\n");
                    int isbn, quantity;
                    scanf("%d %d", &isbn, &quantity);
                    processsale(isbn, quantity);
                }
                break;
            case 3:
                printf("Processing Low-Stock Report...\n");
                generateLowStockReport();
                break;
            case 4:
                printf("Exiting the program.\n");
                break;
            default:
                printf("Invalid option selected.\n");
                break;
        }

        if(choice != 4) {
            printf("\nPress enter to continue...");
            getchar(); getchar();
        }

    } while(choice != 4);

    return 0;
}
