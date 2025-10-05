#include <stdio.h>

int main() {
    char s[100];
    int len = 0;

    printf("Enter a sentence: ");

    char ch;
    while ((ch = getchar()) != '\n' && len < 100) {
        s[len] = ch;
        len++;
    }

    s[len] = '\0';

    printf("Reversed word order: ");

    int end = len - 1;
    while (end >= 0) {
        while (end >= 0 && s[end] == ' ')
            end--;

        if (end < 0)
            break;

        int start = end;
        while (start >= 0 && s[start] != ' ')
            start--;

        for (int i = start + 1; i <= end; i++)
            printf("%c", s[i]);

        if (start > 0)
            printf(" ");

        
        end = start - 1;
    }

    printf("\n");
    return 0;
}
