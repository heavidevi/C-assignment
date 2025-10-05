#include <stdio.h>
#include <string.h>
#include <ctype.h>

int main() {
    char username[50], password[50], loginUser[50], loginPass[50];
    int i, digitCount = 0, upperCount = 0, lowerCount = 0;

    printf("Enter username (5 alphabets): ");
    scanf("%s", username);


    if (strlen(username) != 5) {
        printf("Error:\n    username must be exactly 5 characters.\n");
        return 0;
    }
    for (i = 0; i < 5; i++) {
        if (!isalpha(username[i])) {
            printf("Error:\n    username must only contain alphabets.\n");
            return 0; 
        }
    }

    printf("Enter password (6 chars, must contain digit, upper, lower): ");
    scanf("%s", password);


    if (strlen(password) != 6) {
        printf("Error:\n  Password must be exactly 6 characters.\n");
        return 0;
    }

    i = 0;
    while (password[i] != '\0') {
        isdigit(password[i])? digitCount++:0;
        isupper(password[i])? upperCount++:0;
        islower(password[i])? lowerCount++:0;
        i++;
    }


    if (digitCount == 0) {
        printf("Password must contain at least 1 digit.\n");
        return 0;
    }
    if (upperCount == 0) {
        printf("Password must contain at least 1 uppercase letter.\n");
        return 0;
    }
    if (lowerCount == 0) {
        printf("Password must contain at least 1 lowercase letter.\n");
        return 0;
    }

    printf("\nAccount Created Successfully!\n");


    while (1) {
        printf("\nEnter username: ");
        scanf("%s", loginUser);

        printf("Enter password: ");
        scanf("%s", loginPass);

        if (strcmp(username, loginUser) != 0 || strcmp(password, loginPass) != 0) {
            printf("Invalid credentials. Try again.\n");
            continue; 
        } else {
            printf("Welcome %s, you are now logged in.\n", username);
            break; 
        }
    }

    return 0;
}
