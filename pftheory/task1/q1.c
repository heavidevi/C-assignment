#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>


#define DAILY_LIMIT 5000


float total_amount = 0;
int transaction_number = 0;
int hours[3] = {-1, -1, -1};


int check_country(char country[]) {
    if (strcmp(country, "pakistan") == 0) return 1;
    else if (strcmp(country, "uae") == 0) return 1;
    else return 0;
}

int count_same_hour(int current_hour) {
    int count = 0;

    if (hours[0] == current_hour) count++;
    if (hours[1] == current_hour) count++;
    if (hours[2] == current_hour) count++;

    return count;
}

void shift_hours(int new_hour) {
    hours[2] = hours[1];
    hours[1] = hours[0];
    hours[0] = new_hour;
}


void transaction() {
    float amount;
    char time_str[6];
    int hour, minute;
    char country[50];

    printf("\nEnter transaction amount: ");
    scanf("%f", &amount);

    printf("Enter time (HH:MM): (24 hour format) ");
    scanf("%s", time_str);
    hour=atoi(strtok(time_str, ":"));

    printf("Enter country: ");
    scanf("%s", country);

    total_amount += amount;

    
    if (total_amount > DAILY_LIMIT) {
        printf("Suspicious: Daily spending limit exceeded.\n");
        return;
    }

    
    if (check_country(country) == 0) {
        printf("Suspicious: Country not allowed.\n");
        return;
    }

  
    int same_hour_count = count_same_hour(hour);
    if (same_hour_count >= 3) {
        printf("Suspicious: More than 3 transactions in same hour.\n");
        return;
    }

   
    shift_hours(hour);

    printf("Transaction accepted.\n");

    char choice;
    printf("Do you want to make another transaction? (y/n): ");
    scanf(" %c", &choice);

    

    if (tolower(choice) == 'y') {
        transaction();
    } else {
        printf("Session ended. Total spent: %.2f\n", total_amount);
    }
}

int main() {
    
    transaction();
    return 0;
}



