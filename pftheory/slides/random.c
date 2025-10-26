/*
===============================================================================
                    RANDOM NUMBER GENERATORS IN C - EASY GUIDE
===============================================================================

📚 WHAT ARE RANDOM NUMBER GENERATORS?
-------------------------------------
Random Number Generators (RNGs) are functions that produce sequences of numbers
that appear to be random. In C, these are "pseudo-random" because they follow
a mathematical formula, but the sequence appears random to users.

🎯 WHY DO WE NEED RANDOM NUMBERS?
---------------------------------
- Games (dice rolls, card shuffling, enemy AI)
- Simulations (weather modeling, traffic patterns)
- Cryptography (password generation, encryption keys)
- Testing (generating test data)
- Statistics (sampling, Monte Carlo methods)

*/

#include <stdio.h>
#include <stdlib.h>  // For rand() and srand()
#include <time.h>    // For time() function

/*
===============================================================================
                            1. BASIC RANDOM FUNCTIONS
===============================================================================
*/

void basicRandomDemo() {
    printf("=== BASIC RANDOM NUMBER DEMO ===\n");
    
    // rand() generates random numbers between 0 and RAND_MAX
    printf("RAND_MAX value on this system: %d\n", RAND_MAX);
    
    printf("\n5 Random numbers using rand():\n");
    for(int i = 0; i < 5; i++) {
        int randomNum = rand();
        printf("Random %d: %d\n", i+1, randomNum);
    }
    
    printf("\n❌ PROBLEM: Run this program multiple times - you'll get SAME numbers!\n");
    printf("This happens because rand() uses the same 'seed' every time.\n\n");
}

/*
===============================================================================
                            2. WHAT IS A SEED?
===============================================================================

🌱 SEED CONCEPT:
- A seed is like a "starting point" for the random number formula
- Same seed = Same sequence of "random" numbers
- Different seed = Different sequence of numbers
- Think of it like planting different seeds gives different plants

📝 WHY SEEDS MATTER:
- Default seed is usually 1
- To get truly unpredictable numbers, we need unpredictable seeds
- Time is perfect for this - it's always changing!
*/

void seedDemo() {
    printf("=== SEED DEMONSTRATION ===\n");
    
    // Using fixed seed
    printf("Using fixed seed (123):\n");
    srand(123);  // Set seed to 123
    for(int i = 0; i < 3; i++) {
        printf("Number %d: %d\n", i+1, rand());
    }
    
    printf("\nUsing same fixed seed (123) again:\n");
    srand(123);  // Same seed again
    for(int i = 0; i < 3; i++) {
        printf("Number %d: %d\n", i+1, rand());
    }
    
    printf("👀 Notice: Same seed produces SAME sequence!\n\n");
}

/*
===============================================================================
                            3. TIME FUNCTIONS IN C
===============================================================================

⏰ TIME FUNCTIONS EXPLAINED:

1. time(NULL):
   - Returns current time as seconds since January 1, 1970 (Unix epoch)
   - NULL means we don't want to store time in a variable
   - Perfect for seeding because it changes every second

2. Other time functions:
   - clock() - CPU time used by program
   - difftime() - difference between two times
   - localtime() - converts time to local time structure
*/

void timeDemo() {
    printf("=== TIME FUNCTIONS DEMO ===\n");
    
    // Get current time
    time_t currentTime = time(NULL);
    printf("Current time (seconds since 1970): %ld\n", currentTime);
    
    // Wait and show time changes
    printf("Waiting 2 seconds...\n");
    int count = 0;
    while(count < 2000000000) count++; // Simple delay
    
    time_t newTime = time(NULL);
    printf("Time after delay: %ld\n", newTime);
    printf("Difference: %ld seconds\n", newTime - currentTime);
    
    // Show clock() function
    clock_t start = clock();
    for(int i = 0; i < 1000000; i++); // Some work
    clock_t end = clock();
    
    printf("CPU time used: %ld clock ticks\n", end - start);
    printf("CPU time in seconds: %.2f\n", (double)(end - start) / CLOCKS_PER_SEC);
    printf("\n");
}

/*
===============================================================================
                        4. PROPER RANDOM NUMBER GENERATION
===============================================================================
*/

void properRandomDemo() {
    printf("=== PROPER RANDOM GENERATION ===\n");
    
    // Seed with current time - this makes numbers truly unpredictable!
    srand(time(NULL));
    
    printf("Random numbers with time-based seed:\n");
    for(int i = 0; i < 5; i++) {
        printf("Random %d: %d\n", i+1, rand());
    }
    
    printf("\n✅ Now run the program multiple times - you'll get different numbers!\n\n");
}

/*
===============================================================================
                        5. CONTROLLING RANDOM RANGES
===============================================================================

🎯 COMMON PATTERNS:

1. Random number between 0 and N-1:
   rand() % N

2. Random number between MIN and MAX:
   rand() % (MAX - MIN + 1) + MIN

3. Random decimal between 0.0 and 1.0:
   (double)rand() / RAND_MAX

4. Random decimal between MIN and MAX:
   (double)rand() / RAND_MAX * (MAX - MIN) + MIN
*/

void rangeDemo() {
    printf("=== CONTROLLING RANDOM RANGES ===\n");
    
    srand(time(NULL));
    
    // Dice roll (1-6)
    printf("🎲 Dice rolls (1-6):\n");
    for(int i = 0; i < 5; i++) {
        int dice = rand() % 6 + 1;  // 0-5 becomes 1-6
        printf("Roll %d: %d\n", i+1, dice);
    }
    
    // Random between 10 and 50
    printf("\n📊 Numbers between 10-50:\n");
    for(int i = 0; i < 5; i++) {
        int num = rand() % (50 - 10 + 1) + 10;  // Formula: rand() % (max-min+1) + min
        printf("Number %d: %d\n", i+1, num);
    }
    
    // Random decimals
    printf("\n💯 Random percentages (0.0 - 100.0):\n");
    for(int i = 0; i < 5; i++) {
        double percentage = (double)rand() / RAND_MAX * 100.0;
        printf("Percentage %d: %.2f%%\n", i+1, percentage);
    }
    printf("\n");
}

/*
===============================================================================
                            6. PRACTICAL EXAMPLES
===============================================================================
*/

void practicalExamples() {
    printf("=== PRACTICAL EXAMPLES ===\n");
    
    srand(time(NULL));
    
    // 1. Password generator
    printf("🔐 Random Password Generator:\n");
    char password[9] = "";  // 8 chars + null terminator
    for(int i = 0; i < 8; i++) {
        // Generate random character: A-Z (65-90) or a-z (97-122) or 0-9 (48-57)
        int choice = rand() % 3;
        if(choice == 0) {
            password[i] = 'A' + rand() % 26;  // A-Z
        } else if(choice == 1) {
            password[i] = 'a' + rand() % 26;  // a-z  
        } else {
            password[i] = '0' + rand() % 10;  // 0-9
        }
    }
    password[8] = '\0';  // Null terminator
    printf("Generated password: %s\n", password);
    
    // 2. Coin flip simulator
    printf("\n🪙 Coin Flip Simulator (10 flips):\n");
    int heads = 0, tails = 0;
    for(int i = 0; i < 10; i++) {
        if(rand() % 2 == 0) {
            printf("Flip %d: HEADS\n", i+1);
            heads++;
        } else {
            printf("Flip %d: TAILS\n", i+1);
            tails++;
        }
    }
    printf("Results: %d Heads, %d Tails\n", heads, tails);
    
    // 3. Random array shuffling
    printf("\n🔀 Array Shuffling:\n");
    int arr[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int size = 10;
    
    printf("Original: ");
    for(int i = 0; i < size; i++) printf("%d ", arr[i]);
    
    // Fisher-Yates shuffle algorithm
    for(int i = size - 1; i > 0; i--) {
        int j = rand() % (i + 1);
        // Swap arr[i] and arr[j]
        int temp = arr[i];
        arr[i] = arr[j];
        arr[j] = temp;
    }
    
    printf("\nShuffled: ");
    for(int i = 0; i < size; i++) printf("%d ", arr[i]);
    printf("\n\n");
}

/*
===============================================================================
                            7. BEST PRACTICES & TIPS
===============================================================================
*/

void bestPractices() {
    printf("=== BEST PRACTICES & TIPS ===\n");
    
    printf("✅ DO:\n");
    printf("   - Call srand(time(NULL)) ONCE at program start\n");
    printf("   - Use proper range formulas: rand() %% (max-min+1) + min\n");
    printf("   - Cast to double for decimal ranges: (double)rand()/RAND_MAX\n");
    printf("   - Consider using better RNGs for cryptography\n\n");
    
    printf("❌ DON'T:\n");
    printf("   - Call srand() multiple times (it resets the sequence)\n");
    printf("   - Use rand() without seeding (you'll get same numbers)\n");
    printf("   - Use rand() for security-critical applications\n");
    printf("   - Forget to include <stdlib.h> and <time.h>\n\n");
    
    printf("🔍 COMMON MISTAKES:\n");
    printf("   - rand() %% N has slight bias for large N (use better algorithms for critical apps)\n");
    printf("   - time(NULL) only changes per second (not suitable for rapid generation)\n");
    printf("   - RAND_MAX varies by system (usually 32767 or 2147483647)\n\n");
}

/*
===============================================================================
                            8. ADVANCED TECHNIQUES
===============================================================================
*/

void advancedTechniques() {
    printf("=== ADVANCED TECHNIQUES ===\n");
    
    srand(time(NULL));
    
    // 1. Weighted random selection
    printf("🎯 Weighted Random Selection:\n");
    printf("Choosing fruits: Apple(50%), Orange(30%), Banana(20%)\n");
    
    for(int i = 0; i < 10; i++) {
        int rand_num = rand() % 100;  // 0-99
        char* fruit;
        
        if(rand_num < 50) {
            fruit = "Apple";
        } else if(rand_num < 80) {  // 50-79 (30%)
            fruit = "Orange";  
        } else {  // 80-99 (20%)
            fruit = "Banana";
        }
        
        printf("Selection %d: %s (roll: %d)\n", i+1, fruit, rand_num);
    }
    
    // 2. Random walk simulation
    printf("\n🚶 Random Walk Simulation:\n");
    int position = 0;
    printf("Starting position: %d\n", position);
    
    for(int step = 1; step <= 10; step++) {
        int direction = rand() % 2;  // 0 or 1
        if(direction == 0) {
            position--;
            printf("Step %d: Move LEFT  → Position: %d\n", step, position);
        } else {
            position++;
            printf("Step %d: Move RIGHT → Position: %d\n", step, position);
        }
    }
    
    printf("Final position: %d\n\n", position);
}

/*
===============================================================================
                                MAIN FUNCTION
===============================================================================
*/

int main() {
    printf("🎲 COMPREHENSIVE RANDOM NUMBER GENERATOR GUIDE 🎲\n");
    printf("==================================================\n\n");
    
    // Run all demonstrations
    basicRandomDemo();
    seedDemo();
    timeDemo();
    properRandomDemo();
    rangeDemo();
    practicalExamples();
    bestPractices();
    advancedTechniques();
    
    printf("🎊 SUMMARY:\n");
    printf("----------\n");
    printf("1. Include <stdlib.h> and <time.h>\n");
    printf("2. Call srand(time(NULL)) once at start\n");  
    printf("3. Use rand() to generate random numbers\n");
    printf("4. Apply range formulas for specific ranges\n");
    printf("5. Understand that these are pseudo-random numbers\n\n");
    
    printf("💡 Remember: Practice with different ranges and applications!\n");
    
    return 0;
}

/*
===============================================================================
                            QUICK REFERENCE CARD
===============================================================================

📋 ESSENTIAL FUNCTIONS:
- srand(seed)           → Set random seed (call once)
- rand()                → Generate random number (0 to RAND_MAX)
- time(NULL)            → Get current time (perfect for seeding)
- clock()               → Get CPU time

🎯 COMMON PATTERNS:
- Random 0 to N-1:      rand() % N
- Random MIN to MAX:    rand() % (MAX-MIN+1) + MIN  
- Random 0.0 to 1.0:    (double)rand() / RAND_MAX
- Random float range:   (double)rand()/RAND_MAX * (MAX-MIN) + MIN

🔧 SETUP TEMPLATE:
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
    srand(time(NULL));  // Seed once
    
    // Your random number code here
    int random = rand() % 100;  // 0-99
    
    return 0;
}

===============================================================================
*/