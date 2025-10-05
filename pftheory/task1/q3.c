#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

int main() {
    int age;
    char eyesight_exam, written_test, driving_test, medical_certificate;
    
    system("cls");
    printf("What is your age? ");
    if (scanf("%d", &age) != 1) {
        printf("Invalid input for age.\n");
        return 1;
    }

    if (age >= 18) {
        printf("Did you pass (P) or fail (F) your eyesight exam? ");
        if (scanf(" %c", &eyesight_exam) != 1) {
            printf("Invalid input for eyesight exam.\n");
            return 1;
        }

        if (eyesight_exam == 'P' || eyesight_exam == 'p') {
            system("cls");
            
            printf("Did you pass (P) or fail (F) your written test? ");
            if (scanf(" %c", &written_test) != 1) {
                printf("Invalid input for written test.\n");
                return 1;
            }

            if (written_test == 'P' || written_test == 'p') {
                system("cls");
                printf("Did you pass (P) or fail (F) your driving test? ");
                if (scanf(" %c", &driving_test) != 1) {
                    printf("Invalid input for driving test.\n");
                    return 1;
                }

                if (driving_test == 'P' || driving_test == 'p') {
                    if (age > 60) {
                        system("cls");
                        printf("Do you have a medical fitness certificate (Y/N)? ");
                        if (scanf(" %c", &medical_certificate) != 1) {
                            printf("Invalid input for medical certificate.\n");
                            return 1;
                        }
                        if (medical_certificate == 'Y' || medical_certificate == 'y') {
                            system("cls");
                            printf("You are eligible for the license.\n");
                        } else {
                            printf("You are not eligible.\n");
                        }
                    } else {
                        system("cls");
                        printf("You are eligible for the license.\n");
                    }
                } else {
                    printf("You are not eligible.\n");
                }
            } else {
                printf("You need to retake the written test.\n");
            }
        } else {
            printf("You might need a prescription for glasses.\n");
        }
    } else {
        printf("You are ineligible for a license.\n");
    }

    return 0;
}