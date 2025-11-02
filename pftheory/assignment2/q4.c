#include <stdio.h>


int maxsize = 1;
void Push(int stack[],int top) {
    int value;
    printf("Enter value to push: ");
    scanf("%d", &value);
    stack[top] = value;
}

void Pop(int stack[],int top,int *value) {
    *value = stack[top];
    stack[top] = 0;  
}

void Peek(int stack[], int top) {
    printf("Top element is: %d\n", stack[top]);
}


void Display(int stack[], int top) {
    printf("Stack elements:\n");
    for(int i = top; i >= 0; i--) {
        printf("%d\n", stack[i]);
    }
}

int main() {
    int stack[100] = {0};
    int choice, top = -1, value;

    do {
        printf("\nSTACK OPERATIONS MENU\n");
        printf("1. Push\n");
        printf("2. Pop\n");
        printf("3. Peek\n");
        printf("4. Display\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch(choice) {
            case 1:
                if(top == maxsize - 1) {
                    maxsize *= 2;
                    printf("Stack size increased to %d\n", maxsize);
                }
                top++;
                Push(stack, top);
                break;
            case 2:
                if(top == -1) {
                    printf("Stack underflow! Cannot pop from empty stack.\n");
                } else {
                    Pop(stack, top, &value);
                    printf("Popped value: %d\n", value);
                    top--;
                }
                break;
            case 3:
                if(top == -1) {
                    printf("Stack is empty! No top element.\n");
                } else {
                    Peek(stack, top);
                }
                break;
            case 4:
                if(top == -1) {
                    printf("Stack is empty! No elements to display.\n");
                } else {
                    Display(stack, top);
                }
                break;
            case 5:
                printf("Exiting program.\n");
                break;
            default:
                printf("Invalid choice! Please try again.\n");
        }
    } while(choice != 5);
    return 0;
}





