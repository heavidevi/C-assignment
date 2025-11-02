#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char bittoggle(char letter){
    return letter^18;
}

void reverse(char str[], int size){
    for(int i = 0; i < size/2; i++){
        char temp = str[i];
        str[i] = str[size-1-i];
        str[size-1-i] = temp;
    }
}

char* encode(char str[], int size){
   
    reverse(str, size);
    
    for(int i = 0; i < size; i++){
        str[i] = bittoggle(str[i]);
    }
    str[size] = '\0';
    return str;
}

char* decode(char str[], int size){
    
    for(int i = 0; i < size; i++){
        str[i] = bittoggle(str[i]);
    }
    
    reverse(str, size);
    str[size] = '\0';
    return str;
}

void clear_screen() {
    system("cls");
}


void read_full_message(char message[]) {
    int i = 0;
    char ch;
    

    while((ch = getchar()) == '\n' || ch == ' ') {
        
    }
    
  
    if(ch != '\n' && ch != ' ') {
        message[i] = ch;
        i++;
    }

    if(ch != '\n' && ch != ' ') {
        message[i] = ch;
        i++;
    }
    message[i] = '\0';
}

int main() {
    int choice;
    char message[100];
    char original[100];
    int continue_program = 1;
    
    printf("Welcome to TCS Message Security Tool!\n");
    
    while(continue_program) {
        clear_screen();
        
        printf("=== TCS COURIER MESSAGE TOOL ===\n");
        printf("What do you want to do?\n");
        printf("1. Make message secret (Encode)\n");
        printf("2. Read secret message (Decode)\n");
        printf("3. Exit program\n");
        printf("Choose option (1-3): ");
        
        scanf("%d", &choice);
        
        clear_screen();
        
        if(choice == 1) {
            printf("=== MAKE MESSAGE SECRET ===\n");
            printf("Type your full message (with spaces): ");
            read_full_message(message);
            
            strcpy(original, message);
            int len = strlen(message);
            
            printf("\nMaking your message secret...\n");
            printf("Step 1: Reversing text...\n");
            printf("Step 2: Applying security transformation...\n");
            
            encode(message, len);
            
            printf("\nOriginal message: %s\n", original);
            printf("Secret message: %s\n", message);
            printf("Your message is now safe to send!\n");
            
        } else if(choice == 2) {
            printf("=== READ SECRET MESSAGE ===\n");
            printf("Type the secret message: ");
            read_full_message(message);
            
            strcpy(original, message);
            int len = strlen(message);
            
            printf("\nDecoding your secret message...\n");
            printf("Step 1: Removing security transformation...\n");
            printf("Step 2: Restoring original order...\n");
            
            decode(message, len);
            
            printf("\nSecret message: %s\n", original);
            printf("Real message: %s\n", message);
            printf("Message decoded successfully!\n");
            
        } else if(choice == 3) {
            printf("=== GOODBYE ===\n");
            printf("Thank you for using TCS Security Tool!\n");
            printf("Keep your messages safe!\n");
            continue_program = 0;
            
        } else {
            printf("Wrong choice! Please pick 1, 2, or 3.\n");
        }
        
        if(continue_program) {
            char answer;
            printf("\nDo you want to do something else? (y/n): ");
            scanf(" %c", &answer);
            
            if(answer == 'n' || answer == 'N') {
                printf("\nThank you for using TCS Security Tool!\n");
                continue_program = 0;
            }
        }
    }
    
    return 0;
}


