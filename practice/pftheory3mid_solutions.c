/*
===============================================================================
Programming Fundamentals - Mid Term Exam III
COMPLETE SOLUTIONS WITH IMPLEMENTATIONS
Total Time: 2 Hours | Total Marks: 50
===============================================================================
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>

/*
===============================================================================
QUESTION 1 SOLUTION: Smart Traffic Management System [10 Marks]
===============================================================================
*/

// Global traffic data: traffic[intersection][direction][hour]
int traffic[4][4][24];

// Function to calculate standard deviation
double calculateStandardDeviation(int data[], int size) {
    double sum = 0.0, mean, variance = 0.0;
    
    // Calculate mean
    for (int i = 0; i < size; i++) {
        sum += data[i];
    }
    mean = sum / size;
    
    // Calculate variance
    for (int i = 0; i < size; i++) {
        variance += pow(data[i] - mean, 2);
    }
    variance /= size;
    
    return sqrt(variance);
}

void solveQuestion1() {
    printf("\n=== QUESTION 1: Smart Traffic Management System ===\n");
    
    // Sample data initialization
    srand(time(NULL));
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            for (int k = 0; k < 24; k++) {
                traffic[i][j][k] = rand() % 200; // Random traffic 0-199
            }
        }
    }
    
    // a) Find Rush Hour - hour with maximum city-wide traffic
    int hourlyTotals[24] = {0};
    int maxTraffic = 0, rushHour = 0;
    
    for (int hour = 0; hour < 24; hour++) {
        for (int intersection = 0; intersection < 4; intersection++) {
            for (int direction = 0; direction < 4; direction++) {
                hourlyTotals[hour] += traffic[intersection][direction][hour];
            }
        }
        if (hourlyTotals[hour] > maxTraffic) {
            maxTraffic = hourlyTotals[hour];
            rushHour = hour;
        }
    }
    
    printf("a) Rush Hour: %d:00 with %d total vehicles\n", rushHour, maxTraffic);
    
    // b) Critical Intersection - highest average daily traffic
    double intersectionAverages[4] = {0};
    int criticalIntersection = 0;
    double maxAverage = 0;
    
    for (int intersection = 0; intersection < 4; intersection++) {
        int total = 0;
        for (int direction = 0; direction < 4; direction++) {
            for (int hour = 0; hour < 24; hour++) {
                total += traffic[intersection][direction][hour];
            }
        }
        intersectionAverages[intersection] = total / (4.0 * 24.0);
        if (intersectionAverages[intersection] > maxAverage) {
            maxAverage = intersectionAverages[intersection];
            criticalIntersection = intersection;
        }
    }
    
    printf("b) Critical Intersection: %d with average %.2f vehicles\n", 
           criticalIntersection, maxAverage);
    
    // c) Congestion Pattern - direction with lowest standard deviation
    double minStdDev = 999999.0;
    int consistentDirection = 0;
    const char* directions[] = {"North", "South", "East", "West"};
    
    for (int direction = 0; direction < 4; direction++) {
        int directionData[96]; // 4 intersections × 24 hours
        int index = 0;
        
        for (int intersection = 0; intersection < 4; intersection++) {
            for (int hour = 0; hour < 24; hour++) {
                directionData[index++] = traffic[intersection][direction][hour];
            }
        }
        
        double stdDev = calculateStandardDeviation(directionData, 96);
        if (stdDev < minStdDev) {
            minStdDev = stdDev;
            consistentDirection = direction;
        }
    }
    
    printf("c) Most Consistent Direction: %s (StdDev: %.2f)\n", 
           directions[consistentDirection], minStdDev);
    
    // d) Load Balancing - identify overloaded routes
    printf("d) Load Balancing Alerts:\n");
    int alertCount = 0;
    
    for (int intersection = 0; intersection < 4; intersection++) {
        for (int direction = 0; direction < 4; direction++) {
            for (int hour = 0; hour < 24; hour++) {
                if (traffic[intersection][direction][hour] > 150) {
                    printf("   Alert: Intersection %d, %s direction, Hour %d (%d vehicles)\n",
                           intersection, directions[direction], hour, 
                           traffic[intersection][direction][hour]);
                    alertCount++;
                }
            }
        }
    }
    
    if (alertCount == 0) {
        printf("   No overloaded routes detected.\n");
    }
}

/*
===============================================================================
QUESTION 2 SOLUTION: Cryptocurrency Mining Pool [10 Marks]
===============================================================================
*/

typedef struct {
    char minerID[20];
    double hashRate;
    int uptime;
    double earnings;
    double finalReward;
    double efficiency; // earnings per TH/s
} Miner;

void solveQuestion2() {
    printf("\n=== QUESTION 2: Cryptocurrency Mining Pool ===\n");
    
    // Sample data
    Miner miners[10] = {
        {"MINER001", 15.5, 650, 2500.0, 0, 0},
        {"MINER002", 22.3, 720, 3200.0, 0, 0},
        {"MINER003", 8.7, 180, 800.0, 0, 0},
        {"MINER004", 31.2, 695, 4500.0, 0, 0},
        {"MINER005", 12.1, 540, 1800.0, 0, 0},
        {"MINER006", 45.8, 710, 6200.0, 0, 0},
        {"MINER007", 5.3, 120, 400.0, 0, 0},
        {"MINER008", 28.9, 680, 4100.0, 0, 0},
        {"MINER009", 19.7, 590, 2800.0, 0, 0},
        {"MINER010", 33.4, 700, 4800.0, 0, 0}
    };
    
    int minerCount = 10;
    double dailyPoolReward = 50000.0;
    
    // Calculate total pool hashrate
    double totalHashRate = 0;
    for (int i = 0; i < minerCount; i++) {
        totalHashRate += miners[i].hashRate;
    }
    
    printf("Total Pool HashRate: %.2f TH/s\n", totalHashRate);
    
    // a) Calculate final rewards
    printf("\na) Final Reward Calculations:\n");
    printf("%-10s %8s %6s %10s %12s\n", "MinerID", "HashRate", "Uptime", "Base Reward", "Final Reward");
    printf("-----------------------------------------------------------\n");
    
    for (int i = 0; i < minerCount; i++) {
        // Base reward calculation
        double baseReward = (miners[i].hashRate / totalHashRate) * dailyPoolReward;
        
        // Uptime bonus (15% if uptime > 500 hours)
        double uptimeBonus = 0;
        if (miners[i].uptime > 500) {
            uptimeBonus = baseReward * (miners[i].uptime / 720.0) * 0.15;
        }
        
        // Consistency bonus (10% - simplified, assume all qualify)
        double consistencyBonus = baseReward * 0.10;
        
        // Penalty (-20% if uptime < 200 hours)
        double penalty = 0;
        if (miners[i].uptime < 200) {
            penalty = baseReward * 0.20;
        }
        
        miners[i].finalReward = baseReward + uptimeBonus + consistencyBonus - penalty;
        miners[i].efficiency = miners[i].earnings / miners[i].hashRate;
        
        printf("%-10s %8.1f %6d %10.2f %12.2f\n", 
               miners[i].minerID, miners[i].hashRate, miners[i].uptime, 
               baseReward, miners[i].finalReward);
    }
    
    // b) Top 3 most efficient miners (sorting by efficiency)
    printf("\nb) Top 3 Most Efficient Miners (Earnings per TH/s):\n");
    
    // Simple bubble sort by efficiency
    for (int i = 0; i < minerCount - 1; i++) {
        for (int j = 0; j < minerCount - i - 1; j++) {
            if (miners[j].efficiency < miners[j + 1].efficiency) {
                Miner temp = miners[j];
                miners[j] = miners[j + 1];
                miners[j + 1] = temp;
            }
        }
    }
    
    for (int i = 0; i < 3; i++) {
        printf("   %d. %s - Efficiency: %.2f $/TH/s\n", 
               i + 1, miners[i].minerID, miners[i].efficiency);
    }
    
    // c) Warning list
    printf("\nc) Miners Requiring Warnings:\n");
    int warningCount = 0;
    for (int i = 0; i < minerCount; i++) {
        if (miners[i].uptime < 300 || miners[i].hashRate < 10.0) {
            printf("   WARNING: %s - ", miners[i].minerID);
            if (miners[i].uptime < 300) printf("Low uptime (%d hrs) ", miners[i].uptime);
            if (miners[i].hashRate < 10.0) printf("Low hashrate (%.1f TH/s)", miners[i].hashRate);
            printf("\n");
            warningCount++;
        }
    }
    if (warningCount == 0) {
        printf("   All miners performing adequately.\n");
    }
    
    // d) Dynamic difficulty adjustment
    double targetBlockTime = 10.0; // minutes
    double currentBlockTime = 8.5; // estimated current time
    double difficultyMultiplier = targetBlockTime / currentBlockTime;
    
    printf("\nd) Dynamic Difficulty Adjustment:\n");
    printf("   Current total hashrate: %.2f TH/s\n", totalHashRate);
    printf("   Target block time: %.1f minutes\n", targetBlockTime);
    printf("   Current block time: %.1f minutes\n", currentBlockTime);
    printf("   Suggested difficulty multiplier: %.3f\n", difficultyMultiplier);
}

/*
===============================================================================
QUESTION 3 SOLUTION: DNA Sequence Analysis Engine [10 Marks]
===============================================================================
*/

// KMP Algorithm for pattern matching
void computeLPS(char* pattern, int M, int* lps) {
    int len = 0;
    lps[0] = 0;
    int i = 1;
    
    while (i < M) {
        if (pattern[i] == pattern[len]) {
            len++;
            lps[i] = len;
            i++;
        } else {
            if (len != 0) {
                len = lps[len - 1];
            } else {
                lps[i] = 0;
                i++;
            }
        }
    }
}

int KMPSearch(char* text, char* pattern) {
    int M = strlen(pattern);
    int N = strlen(text);
    int* lps = (int*)malloc(sizeof(int) * M);
    int count = 0;
    
    computeLPS(pattern, M, lps);
    
    int i = 0; // index for text
    int j = 0; // index for pattern
    
    while (i < N) {
        if (pattern[j] == text[i]) {
            j++;
            i++;
        }
        
        if (j == M) {
            printf("   Pattern found at index %d\n", i - j);
            count++;
            j = lps[j - 1];
        } else if (i < N && pattern[j] != text[i]) {
            if (j != 0) {
                j = lps[j - 1];
            } else {
                i++;
            }
        }
    }
    
    free(lps);
    return count;
}

void generateComplement(char* sequence, char* complement) {
    int len = strlen(sequence);
    for (int i = 0; i < len; i++) {
        switch (sequence[len - 1 - i]) { // Reverse while complementing
            case 'A': complement[i] = 'T'; break;
            case 'T': complement[i] = 'A'; break;
            case 'G': complement[i] = 'C'; break;
            case 'C': complement[i] = 'G'; break;
            default: complement[i] = 'N'; break;
        }
    }
    complement[len] = '\0';
}

int findORFs(char* sequence) {
    int len = strlen(sequence);
    int orfCount = 0;
    
    printf("   Open Reading Frames found:\n");
    
    for (int frame = 0; frame < 3; frame++) {
        for (int i = frame; i < len - 5; i += 3) {
            if (strncmp(&sequence[i], "ATG", 3) == 0) {
                // Found start codon, look for stop codons
                for (int j = i + 3; j < len - 2; j += 3) {
                    if (strncmp(&sequence[j], "TAA", 3) == 0 || 
                        strncmp(&sequence[j], "TAG", 3) == 0 || 
                        strncmp(&sequence[j], "TGA", 3) == 0) {
                        printf("     Frame %d: ORF from position %d to %d (length: %d)\n", 
                               frame + 1, i, j + 2, j + 2 - i + 1);
                        orfCount++;
                        i = j; // Move past this ORF
                        break;
                    }
                }
            }
        }
    }
    
    return orfCount;
}

double calculateSimilarity(char* seq1, char* seq2) {
    int len1 = strlen(seq1);
    int len2 = strlen(seq2);
    int minLen = (len1 < len2) ? len1 : len2;
    int matches = 0;
    
    for (int i = 0; i < minLen; i++) {
        if (seq1[i] == seq2[i]) {
            matches++;
        }
    }
    
    return (double)matches / minLen * 100.0;
}

void solveQuestion3() {
    printf("\n=== QUESTION 3: DNA Sequence Analysis Engine ===\n");
    
    char dnaSequence[] = "ATGCGATCGATGAAATCGATGCCCTAGATGTTATAATCGATGCCC";
    char pattern[] = "ATCG";
    char complement[100];
    char sequence2[] = "ATGCGATCGATGAAATCGATGCCCTAGATGTTATAATCGATGAAA";
    
    printf("DNA Sequence: %s\n", dnaSequence);
    printf("Sequence Length: %lu bases\n", strlen(dnaSequence));
    
    // a) Pattern matching using KMP algorithm
    printf("\na) Pattern Matching (searching for '%s'):\n", pattern);
    int matches = KMPSearch(dnaSequence, pattern);
    printf("   Total matches found: %d\n", matches);
    
    // b) Generate complementary strand
    printf("\nb) Complementary Strand Analysis:\n");
    generateComplement(dnaSequence, complement);
    printf("   Original:    %s\n", dnaSequence);
    printf("   Complement:  %s\n", complement);
    
    // Check for palindromes (sequences that match their complement)
    if (strcmp(dnaSequence, complement) == 0) {
        printf("   This sequence is palindromic!\n");
    } else {
        printf("   This sequence is not palindromic.\n");
    }
    
    // c) Reading frame analysis and ORF detection
    printf("\nc) Open Reading Frame Analysis:\n");
    int orfs = findORFs(dnaSequence);
    printf("   Total ORFs found: %d\n", orfs);
    
    // d) Sequence similarity
    printf("\nd) Sequence Similarity Analysis:\n");
    printf("   Sequence 1: %s\n", dnaSequence);
    printf("   Sequence 2: %s\n", sequence2);
    double similarity = calculateSimilarity(dnaSequence, sequence2);
    printf("   Similarity: %.2f%%\n", similarity);
    
    // Additional analysis - GC content
    int gcCount = 0;
    for (int i = 0; i < strlen(dnaSequence); i++) {
        if (dnaSequence[i] == 'G' || dnaSequence[i] == 'C') {
            gcCount++;
        }
    }
    double gcContent = (double)gcCount / strlen(dnaSequence) * 100.0;
    printf("   GC Content: %.2f%%\n", gcContent);
}

/*
===============================================================================
QUESTION 4 SOLUTION: Advanced Memory Pool Manager [10 Marks]
===============================================================================
*/

#define POOL_SIZE 10000

typedef struct BlockHeader {
    size_t size;
    int isFree;
    struct BlockHeader* next;
} BlockHeader;

char memoryPool[POOL_SIZE];
BlockHeader* freeList = NULL;
int isInitialized = 0;

void initializeMemoryPool() {
    if (isInitialized) return;
    
    freeList = (BlockHeader*)memoryPool;
    freeList->size = POOL_SIZE - sizeof(BlockHeader);
    freeList->isFree = 1;
    freeList->next = NULL;
    isInitialized = 1;
}

void* myMalloc(size_t size) {
    if (!isInitialized) initializeMemoryPool();
    
    // Align size to 8 bytes
    size = (size + 7) & ~7;
    
    BlockHeader* current = freeList;
    BlockHeader* prev = NULL;
    
    while (current) {
        if (current->isFree && current->size >= size) {
            // Found suitable block
            if (current->size > size + sizeof(BlockHeader)) {
                // Split the block
                BlockHeader* newBlock = (BlockHeader*)((char*)current + sizeof(BlockHeader) + size);
                newBlock->size = current->size - size - sizeof(BlockHeader);
                newBlock->isFree = 1;
                newBlock->next = current->next;
                
                current->size = size;
                current->next = newBlock;
            }
            
            current->isFree = 0;
            return (char*)current + sizeof(BlockHeader);
        }
        prev = current;
        current = current->next;
    }
    
    return NULL; // No suitable block found
}

void myFree(void* ptr) {
    if (!ptr) return;
    
    BlockHeader* block = (BlockHeader*)((char*)ptr - sizeof(BlockHeader));
    block->isFree = 1;
    
    // Coalesce with next block if it's free
    if (block->next && block->next->isFree) {
        block->size += block->next->size + sizeof(BlockHeader);
        block->next = block->next->next;
    }
    
    // Coalesce with previous block if it's free
    BlockHeader* current = freeList;
    while (current && current->next != block) {
        current = current->next;
    }
    
    if (current && current->isFree) {
        current->size += block->size + sizeof(BlockHeader);
        current->next = block->next;
    }
}

void defragment() {
    BlockHeader* current = freeList;
    
    while (current && current->next) {
        if (current->isFree && current->next->isFree) {
            // Merge adjacent free blocks
            current->size += current->next->size + sizeof(BlockHeader);
            current->next = current->next->next;
        } else {
            current = current->next;
        }
    }
}

void printMemoryMap() {
    printf("Memory Pool Layout:\n");
    printf("Address    Size    Status\n");
    printf("------------------------\n");
    
    BlockHeader* current = freeList;
    while (current) {
        printf("%p  %6zu  %s\n", 
               current, 
               current->size, 
               current->isFree ? "FREE" : "ALLOCATED");
        current = current->next;
    }
}

void solveQuestion4() {
    printf("\n=== QUESTION 4: Advanced Memory Pool Manager ===\n");
    
    // Initialize memory pool
    initializeMemoryPool();
    
    printf("Memory pool initialized with %d bytes\n", POOL_SIZE);
    
    // Test allocations
    printf("\na) Testing Memory Allocations:\n");
    void* ptr1 = myMalloc(100);
    void* ptr2 = myMalloc(200);
    void* ptr3 = myMalloc(150);
    
    printf("Allocated 100 bytes at: %p\n", ptr1);
    printf("Allocated 200 bytes at: %p\n", ptr2);
    printf("Allocated 150 bytes at: %p\n", ptr3);
    
    printf("\nb) Memory Map after allocations:\n");
    printMemoryMap();
    
    // Test deallocation
    printf("\nc) Testing Deallocation:\n");
    myFree(ptr2);
    printf("Freed 200-byte block\n");
    
    printf("Memory Map after freeing middle block:\n");
    printMemoryMap();
    
    // Test defragmentation
    printf("\nd) Testing Defragmentation:\n");
    myFree(ptr1);
    myFree(ptr3);
    printf("Freed remaining blocks\n");
    
    defragment();
    printf("Memory Map after defragmentation:\n");
    printMemoryMap();
    
    // Calculate fragmentation
    BlockHeader* current = freeList;
    int freeBlocks = 0;
    size_t totalFree = 0;
    
    while (current) {
        if (current->isFree) {
            freeBlocks++;
            totalFree += current->size;
        }
        current = current->next;
    }
    
    double fragmentation = (freeBlocks > 1) ? 
        (double)(freeBlocks - 1) / freeBlocks * 100.0 : 0.0;
    
    printf("\ne) Memory Statistics:\n");
    printf("Total free memory: %zu bytes\n", totalFree);
    printf("Free blocks: %d\n", freeBlocks);
    printf("Fragmentation: %.2f%%\n", fragmentation);
}

/*
===============================================================================
QUESTION 5 SOLUTION: Real-time Stock Trading Algorithm [10 Marks]
===============================================================================
*/

typedef struct {
    char symbol[10];
    double price;
    long long timestamp;
    int volume;
} StockData;

typedef struct {
    char symbol[10];
    double buyPrice;
    int quantity;
    long long buyTime;
    double stopLoss;
    double takeProfit;
} Position;

#define MAX_POSITIONS 10
#define PRICE_HISTORY_SIZE 100

typedef struct {
    StockData priceHistory[PRICE_HISTORY_SIZE];
    int historyIndex;
    int historyCount;
    double ma5, ma20;
    double rsi;
    int avgVolume;
} TradingData;

Position portfolio[MAX_POSITIONS];
int portfolioSize = 0;
double portfolioValue = 100000.0; // $100K starting capital

void updateMovingAverages(TradingData* data) {
    if (data->historyCount < 5) return;
    
    // Calculate 5-period MA
    double sum5 = 0;
    for (int i = 0; i < 5; i++) {
        int index = (data->historyIndex - 1 - i + PRICE_HISTORY_SIZE) % PRICE_HISTORY_SIZE;
        sum5 += data->priceHistory[index].price;
    }
    data->ma5 = sum5 / 5.0;
    
    // Calculate 20-period MA
    if (data->historyCount >= 20) {
        double sum20 = 0;
        for (int i = 0; i < 20; i++) {
            int index = (data->historyIndex - 1 - i + PRICE_HISTORY_SIZE) % PRICE_HISTORY_SIZE;
            sum20 += data->priceHistory[index].price;
        }
        data->ma20 = sum20 / 20.0;
    }
}

void updateRSI(TradingData* data) {
    if (data->historyCount < 15) return;
    
    double gains = 0, losses = 0;
    
    for (int i = 1; i < 14; i++) {
        int currIndex = (data->historyIndex - 1 - i + PRICE_HISTORY_SIZE) % PRICE_HISTORY_SIZE;
        int prevIndex = (currIndex - 1 + PRICE_HISTORY_SIZE) % PRICE_HISTORY_SIZE;
        
        double change = data->priceHistory[currIndex].price - data->priceHistory[prevIndex].price;
        
        if (change > 0) {
            gains += change;
        } else {
            losses += (-change);
        }
    }
    
    double avgGain = gains / 14.0;
    double avgLoss = losses / 14.0;
    
    if (avgLoss == 0) {
        data->rsi = 100.0;
    } else {
        double rs = avgGain / avgLoss;
        data->rsi = 100.0 - (100.0 / (1.0 + rs));
    }
}

int shouldBuy(TradingData* data, StockData* current) {
    // Moving Average Crossover
    int maCrossover = (data->ma5 > data->ma20) && (data->historyCount >= 20);
    
    // RSI Oversold
    int rsiOversold = (data->rsi < 30) && (data->historyCount >= 15);
    
    // Volume Analysis
    int highVolume = (current->volume > data->avgVolume * 1.5);
    
    // Risk Management - check if we have room for new position
    int portfolioSpace = (portfolioSize < MAX_POSITIONS);
    
    // Position sizing - don't risk more than 2% of portfolio
    double maxRisk = portfolioValue * 0.02;
    double positionSize = maxRisk / (current->price * 0.1); // 10% stop loss
    
    return maCrossover && rsiOversold && highVolume && portfolioSpace && (positionSize > 0);
}

int shouldSell(Position* pos, StockData* current) {
    // Stop loss
    if (current->price <= pos->stopLoss) {
        return 1;
    }
    
    // Take profit
    if (current->price >= pos->takeProfit) {
        return 1;
    }
    
    return 0;
}

void addPosition(char* symbol, double price, int quantity) {
    if (portfolioSize < MAX_POSITIONS) {
        strcpy(portfolio[portfolioSize].symbol, symbol);
        portfolio[portfolioSize].buyPrice = price;
        portfolio[portfolioSize].quantity = quantity;
        portfolio[portfolioSize].buyTime = time(NULL);
        portfolio[portfolioSize].stopLoss = price * 0.9; // 10% stop loss
        portfolio[portfolioSize].takeProfit = price * 1.2; // 20% take profit
        portfolioSize++;
    }
}

void removePosition(int index) {
    for (int i = index; i < portfolioSize - 1; i++) {
        portfolio[i] = portfolio[i + 1];
    }
    portfolioSize--;
}

void solveQuestion5() {
    printf("\n=== QUESTION 5: Real-time Stock Trading Algorithm ===\n");
    
    // Sample trading data for AAPL
    TradingData aaplData = {0};
    
    // Initialize with sample price history
    double samplePrices[] = {150.0, 151.2, 149.8, 152.1, 153.5, 152.0, 154.2, 
                            155.1, 153.8, 156.2, 157.0, 155.5, 158.1, 159.2, 
                            157.8, 160.1, 161.5, 159.9, 162.3, 163.1, 161.7, 
                            164.2, 165.8, 163.4, 166.1, 167.3, 165.9, 168.2};
    
    int sampleVolumes[] = {1000000, 1200000, 800000, 1500000, 1800000, 900000, 
                          1600000, 1700000, 1100000, 2000000, 2200000, 1300000,
                          1900000, 2100000, 1400000, 2300000, 2500000, 1500000,
                          2400000, 2600000, 1600000, 2700000, 2800000, 1700000,
                          2900000, 3000000, 1800000, 3100000};
    
    // Populate price history
    for (int i = 0; i < 28; i++) {
        aaplData.priceHistory[i].price = samplePrices[i];
        aaplData.priceHistory[i].volume = sampleVolumes[i];
        aaplData.priceHistory[i].timestamp = time(NULL) - (28 - i) * 3600; // 1 hour apart
        strcpy(aaplData.priceHistory[i].symbol, "AAPL");
        aaplData.historyIndex = (i + 1) % PRICE_HISTORY_SIZE;
        aaplData.historyCount = i + 1;
    }
    
    // Calculate average volume
    long long totalVolume = 0;
    for (int i = 0; i < aaplData.historyCount; i++) {
        totalVolume += aaplData.priceHistory[i].volume;
    }
    aaplData.avgVolume = totalVolume / aaplData.historyCount;
    
    printf("Trading Algorithm Simulation for AAPL\n");
    printf("Portfolio Value: $%.2f\n", portfolioValue);
    printf("Average Volume: %d\n", aaplData.avgVolume);
    
    // Update technical indicators
    updateMovingAverages(&aaplData);
    updateRSI(&aaplData);
    
    printf("\na) Technical Indicators:\n");
    printf("5-period MA: $%.2f\n", aaplData.ma5);
    printf("20-period MA: $%.2f\n", aaplData.ma20);
    printf("RSI: %.2f\n", aaplData.rsi);
    
    // Simulate current market data
    StockData currentData = {"AAPL", 169.5, time(NULL), 3200000};
    
    printf("\nb) Current Market Data:\n");
    printf("Symbol: %s\n", currentData.symbol);
    printf("Current Price: $%.2f\n", currentData.price);
    printf("Current Volume: %d\n", currentData.volume);
    
    // Trading decision
    printf("\nc) Trading Decision Analysis:\n");
    
    if (shouldBuy(&aaplData, &currentData)) {
        double maxRisk = portfolioValue * 0.02;
        int quantity = (int)(maxRisk / (currentData.price * 0.1));
        
        printf("BUY SIGNAL GENERATED!\n");
        printf("Recommended quantity: %d shares\n", quantity);
        printf("Total investment: $%.2f\n", quantity * currentData.price);
        
        addPosition(currentData.symbol, currentData.price, quantity);
        printf("Position added to portfolio.\n");
    } else {
        printf("No buy signal - conditions not met:\n");
        printf("- MA Crossover: %s\n", (aaplData.ma5 > aaplData.ma20) ? "✓" : "✗");
        printf("- RSI Oversold: %s\n", (aaplData.rsi < 30) ? "✓" : "✗");
        printf("- High Volume: %s\n", (currentData.volume > aaplData.avgVolume * 1.5) ? "✓" : "✗");
        printf("- Portfolio Space: %s\n", (portfolioSize < MAX_POSITIONS) ? "✓" : "✗");
    }
    
    // Portfolio management
    printf("\nd) Portfolio Management:\n");
    printf("Current Positions: %d/%d\n", portfolioSize, MAX_POSITIONS);
    
    if (portfolioSize > 0) {
        printf("Active Positions:\n");
        printf("%-6s %8s %6s %10s %10s\n", "Symbol", "Price", "Qty", "Stop Loss", "Take Profit");
        printf("-----------------------------------------------\n");
        
        for (int i = 0; i < portfolioSize; i++) {
            printf("%-6s %8.2f %6d %10.2f %10.2f\n",
                   portfolio[i].symbol,
                   portfolio[i].buyPrice,
                   portfolio[i].quantity,
                   portfolio[i].stopLoss,
                   portfolio[i].takeProfit);
        }
        
        // Check for sell signals
        for (int i = 0; i < portfolioSize; i++) {
            if (shouldSell(&portfolio[i], &currentData)) {
                double profit = (currentData.price - portfolio[i].buyPrice) * portfolio[i].quantity;
                printf("SELL SIGNAL for %s - Profit/Loss: $%.2f\n", 
                       portfolio[i].symbol, profit);
            }
        }
    }
    
    // Risk analysis
    printf("\ne) Risk Analysis:\n");
    double totalExposure = 0;
    for (int i = 0; i < portfolioSize; i++) {
        totalExposure += portfolio[i].buyPrice * portfolio[i].quantity;
    }
    
    double exposurePercent = (totalExposure / portfolioValue) * 100.0;
    printf("Total market exposure: $%.2f (%.2f%% of portfolio)\n", 
           totalExposure, exposurePercent);
    printf("Maximum risk per trade: $%.2f (2%% of portfolio)\n", 
           portfolioValue * 0.02);
    
    if (exposurePercent > 80.0) {
        printf("WARNING: High portfolio exposure detected!\n");
    }
}

/*
===============================================================================
MAIN FUNCTION - RUN ALL SOLUTIONS
===============================================================================
*/

int main(void) {
    printf("Programming Fundamentals - Advanced Critical Thinking Assessment\n");
    printf("COMPLETE SOLUTIONS IMPLEMENTATION\n");
    printf("================================================================\n");
    
    // Run all solutions
    solveQuestion1();
    solveQuestion2();
    solveQuestion3();
    solveQuestion4();
    solveQuestion5();
    
    printf("\n================================================================\n");
    printf("All solutions completed successfully!\n");
    printf("================================================================\n");
    
    return 0;
}

/*
===============================================================================
ADDITIONAL NOTES AND EXPLANATIONS
===============================================================================

QUESTION 1 - Smart Traffic Management:
- Uses 3D array traversal with nested loops
- Implements statistical calculations (mean, standard deviation)
- Demonstrates data aggregation across multiple dimensions
- Shows practical application of arrays in real-world scenarios

QUESTION 2 - Cryptocurrency Mining Pool:
- Demonstrates parallel array processing
- Implements complex reward algorithms with multiple conditions
- Shows sorting and ranking algorithms
- Illustrates real-world financial calculations

QUESTION 3 - DNA Sequence Analysis:
- Implements advanced string algorithms (KMP for pattern matching)
- Shows biological sequence processing
- Demonstrates efficient search algorithms
- Illustrates bioinformatics applications

QUESTION 4 - Memory Pool Manager:
- Implements custom memory management using static array
- Shows linked list data structures within memory pool
- Demonstrates memory coalescing and defragmentation
- Illustrates low-level memory management concepts

QUESTION 5 - Stock Trading Algorithm:
- Implements real-time data processing with circular buffers
- Shows technical indicator calculations (MA, RSI)
- Demonstrates financial algorithm implementation
- Illustrates complex decision-making systems

Each solution demonstrates:
1. Advanced data structure usage
2. Complex algorithm implementation
3. Real-world problem solving
4. Mathematical computations
5. Efficient memory management
6. Error handling and edge cases

These solutions represent advanced C programming concepts suitable for
comprehensive assessment of programming fundamentals knowledge.
*/
