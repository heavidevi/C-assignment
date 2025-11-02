#include <stdio.h>

float add(float a, float b) {
    return a + b;
}

float subtract(float a, float b) {
    return a - b;
}

float multiply(float a, float b) {
    return a * b;
}

float divide(float a, float b) {
    if(b != 0)
        return a / b;
    else {
        printf("Error: Division by zero\n");
        return 0;
    }
}

int main() {
    float (*ops[4])(float, float) = {add, subtract, multiply, divide};
    char symbols[4] = {'+', '-', '*', '/'};
    
    float num1, num2;
    char op;
    int choice = -1;
    
    printf("Enter first number: ");
    scanf("%f", &num1);
    printf("Enter operator (+, -, *, /): ");
    scanf(" %c", &op);
    printf("Enter second number: ");
    scanf("%f", &num2);
    
    for(int i = 0; i < 4; i++) {
        if(symbols[i] == op) {
            choice = i;
            break;
        }
    }
    
    if(choice != -1) {
        float result = ops[choice](num1, num2);
        printf("Result: %.2f %c %.2f = %.2f\n", num1, op, num2, result);
    } else {
        printf("Invalid operator\n");
    }
    
    return 0;
}