#include <stdio.h>

int main() {
    char a1, a2, a3, a4, a5, a6, a7, a8, a9, a10;
    char b1, b2, b3, b4, b5, b6, b7, b8, b9, b10;
    char d1, d2, d3, d4, d5, d6, d7, d8, d9, d10;
    char e1, e2, e3, e4, e5, e6, e7, e8, e9, e10;
    char f1, f2, f3, f4, f5, f6, f7, f8, f9, f10;
    
    printf("Enter a sentence: ");
    
    char input;
    int len = 0;
    int spaces = 0;
    while ((input = getchar()) != '\n' && len < 50) {
        len++;
        
        int pos = len - 1;
        
        for (int i = 0; i < 50; i++) {
            if (i == pos) {
                if (i == 0) a1 = input;
                else if (i == 1) a2 = input;
                else if (i == 2) a3 = input;
                else if (i == 3) a4 = input;
                else if (i == 4) a5 = input;
                else if (i == 5) a6 = input;
                else if (i == 6) a7 = input;
                else if (i == 7) a8 = input;
                else if (i == 8) a9 = input;
                else if (i == 9) a10 = input;
                else if (i == 10) b1 = input;
                else if (i == 11) b2 = input;
                else if (i == 12) b3 = input;
                else if (i == 13) b4 = input;
                else if (i == 14) b5 = input;
                else if (i == 15) b6 = input;
                else if (i == 16) b7 = input;
                else if (i == 17) b8 = input;
                else if (i == 18) b9 = input;
                else if (i == 19) b10 = input;
                else if (i == 20) d1 = input;
                else if (i == 21) d2 = input;
                else if (i == 22) d3 = input;
                else if (i == 23) d4 = input;
                else if (i == 24) d5 = input;
                else if (i == 25) d6 = input;
                else if (i == 26) d7 = input;
                else if (i == 27) d8 = input;
                else if (i == 28) d9 = input;
                else if (i == 29) d10 = input;
                else if (i == 30) e1 = input;
                else if (i == 31) e2 = input;
                else if (i == 32) e3 = input;
                else if (i == 33) e4 = input;
                else if (i == 34) e5 = input;
                else if (i == 35) e6 = input;
                else if (i == 36) e7 = input;
                else if (i == 37) e8 = input;
                else if (i == 38) e9 = input;
                else if (i == 39) e10 = input;
                else if (i == 40) f1 = input;
                else if (i == 41) f2 = input;
                else if (i == 42) f3 = input;
                else if (i == 43) f4 = input;
                else if (i == 44) f5 = input;
                else if (i == 45) f6 = input;
                else if (i == 46) f7 = input;
                else if (i == 47) f8 = input;
                else if (i == 48) f9 = input;
                else if (i == 49) f10 = input;
                break;
            }
        }
        
        if (input == ' ') {
            spaces++;
        }
    }
    
    printf("Reversed word order: ");
    
    int words = spaces + 1;
    for (int word = words; word >= 1; word--) {
        int start, end;
        
        int curr_word = 1;
        start = 1;
        
        for (int pos = 1; pos <= len; pos++) {
            char curr = '\0';
            int idx = pos - 1;
            
            for (int j = 0; j < 50; j++) {
                if (j == idx) {
                    if (j == 0) curr = a1;
                    else if (j == 1) curr = a2;
                    else if (j == 2) curr = a3;
                    else if (j == 3) curr = a4;
                    else if (j == 4) curr = a5;
                    else if (j == 5) curr = a6;
                    else if (j == 6) curr = a7;
                    else if (j == 7) curr = a8;
                    else if (j == 8) curr = a9;
                    else if (j == 9) curr = a10;
                    else if (j == 10) curr = b1;
                    else if (j == 11) curr = b2;
                    else if (j == 12) curr = b3;
                    else if (j == 13) curr = b4;
                    else if (j == 14) curr = b5;
                    else if (j == 15) curr = b6;
                    else if (j == 16) curr = b7;
                    else if (j == 17) curr = b8;
                    else if (j == 18) curr = b9;
                    else if (j == 19) curr = b10;
                    else if (j == 20) curr = d1;
                    else if (j == 21) curr = d2;
                    else if (j == 22) curr = d3;
                    else if (j == 23) curr = d4;
                    else if (j == 24) curr = d5;
                    else if (j == 25) curr = d6;
                    else if (j == 26) curr = d7;
                    else if (j == 27) curr = d8;
                    else if (j == 28) curr = d9;
                    else if (j == 29) curr = d10;
                    else if (j == 30) curr = e1;
                    else if (j == 31) curr = e2;
                    else if (j == 32) curr = e3;
                    else if (j == 33) curr = e4;
                    else if (j == 34) curr = e5;
                    else if (j == 35) curr = e6;
                    else if (j == 36) curr = e7;
                    else if (j == 37) curr = e8;
                    else if (j == 38) curr = e9;
                    else if (j == 39) curr = e10;
                    else if (j == 40) curr = f1;
                    else if (j == 41) curr = f2;
                    else if (j == 42) curr = f3;
                    else if (j == 43) curr = f4;
                    else if (j == 44) curr = f5;
                    else if (j == 45) curr = f6;
                    else if (j == 46) curr = f7;
                    else if (j == 47) curr = f8;
                    else if (j == 48) curr = f9;
                    else if (j == 49) curr = f10;
                    break;
                }
            }
            
            if (curr == ' ') {
                if (curr_word == word) {
                    end = pos - 1;
                    break;
                } else {
                    curr_word++;
                    if (curr_word == word) {
                        start = pos + 1;
                    }
                }
            } else if (pos == len) {
                if (curr_word == word) {
                    end = pos;
                }
            }
        }
        
        if (curr_word == word && word == words) {
            end = len;
        }
        
        for (int pos = start; pos <= end; pos++) {
            char output = '\0';
            int out_idx = pos - 1;
            
            for (int k = 0; k < 50; k++) {
                if (k == out_idx) {
                    if (k == 0) output = a1;
                    else if (k == 1) output = a2;
                    else if (k == 2) output = a3;
                    else if (k == 3) output = a4;
                    else if (k == 4) output = a5;
                    else if (k == 5) output = a6;
                    else if (k == 6) output = a7;
                    else if (k == 7) output = a8;
                    else if (k == 8) output = a9;
                    else if (k == 9) output = a10;
                    else if (k == 10) output = b1;
                    else if (k == 11) output = b2;
                    else if (k == 12) output = b3;
                    else if (k == 13) output = b4;
                    else if (k == 14) output = b5;
                    else if (k == 15) output = b6;
                    else if (k == 16) output = b7;
                    else if (k == 17) output = b8;
                    else if (k == 18) output = b9;
                    else if (k == 19) output = b10;
                    else if (k == 20) output = d1;
                    else if (k == 21) output = d2;
                    else if (k == 22) output = d3;
                    else if (k == 23) output = d4;
                    else if (k == 24) output = d5;
                    else if (k == 25) output = d6;
                    else if (k == 26) output = d7;
                    else if (k == 27) output = d8;
                    else if (k == 28) output = d9;
                    else if (k == 29) output = d10;
                    else if (k == 30) output = e1;
                    else if (k == 31) output = e2;
                    else if (k == 32) output = e3;
                    else if (k == 33) output = e4;
                    else if (k == 34) output = e5;
                    else if (k == 35) output = e6;
                    else if (k == 36) output = e7;
                    else if (k == 37) output = e8;
                    else if (k == 38) output = e9;
                    else if (k == 39) output = e10;
                    else if (k == 40) output = f1;
                    else if (k == 41) output = f2;
                    else if (k == 42) output = f3;
                    else if (k == 43) output = f4;
                    else if (k == 44) output = f5;
                    else if (k == 45) output = f6;
                    else if (k == 46) output = f7;
                    else if (k == 47) output = f8;
                    else if (k == 48) output = f9;
                    else if (k == 49) output = f10;
                    break;
                }
            }
            
            printf("%c", output);
        }
        
        if (word > 1) {
            printf(" ");
        }
    }
    
    printf("\n");
    return 0;
}
