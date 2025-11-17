/*
===============================================================================
QUESTION 2 SOLUTION: Cryptocurrency Mining Pool
Programming Fundamentals - Mid Term Exam III
===============================================================================
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>

#define MAX_MINERS 100

typedef struct {
    char minerID[20];
    double hashRate;        // TH/s
    int uptime;            // Hours in last 30 days
    double earnings;       // Total earnings in last 30 days
    double finalReward;    // Calculated final reward
    double efficiency;     // Earnings per TH/s ratio
    int warningFlag;       // 1 if miner needs warning
} Miner;

Miner miners[MAX_MINERS];
int minerCount = 0;
double dailyPoolReward = 50000.0; // $50,000

void initializeMinerData() {
    printf("Initializing mining pool data...\n");
    
    // Sample realistic miner data
    strcpy(miners[0].minerID, "CRYPTO_KING_01");
    miners[0].hashRate = 45.8;
    miners[0].uptime = 710;
    miners[0].earnings = 6200.0;
    
    strcpy(miners[1].minerID, "BITCOIN_MINER_X");
    miners[1].hashRate = 33.4;
    miners[1].uptime = 700;
    miners[1].earnings = 4800.0;
    
    strcpy(miners[2].minerID, "HASH_MASTER_99");
    miners[2].hashRate = 31.2;
    miners[2].uptime = 695;
    miners[2].earnings = 4500.0;
    
    strcpy(miners[3].minerID, "MINING_GIANT_7");
    miners[3].hashRate = 28.9;
    miners[3].uptime = 680;
    miners[3].earnings = 4100.0;
    
    strcpy(miners[4].minerID, "CRYPTO_HUNTER");
    miners[4].hashRate = 22.3;
    miners[4].uptime = 720;
    miners[4].earnings = 3200.0;
    
    strcpy(miners[5].minerID, "DIGITAL_GOLD_M");
    miners[5].hashRate = 19.7;
    miners[5].uptime = 590;
    miners[5].earnings = 2800.0;
    
    strcpy(miners[6].minerID, "BLOCK_FINDER_5");
    miners[6].hashRate = 15.5;
    miners[6].uptime = 650;
    miners[6].earnings = 2500.0;
    
    strcpy(miners[7].minerID, "HASH_WARRIOR");
    miners[7].hashRate = 12.1;
    miners[7].uptime = 540;
    miners[7].earnings = 1800.0;
    
    strcpy(miners[8].minerID, "SMALL_MINER_01");
    miners[8].hashRate = 8.7;
    miners[8].uptime = 180;
    miners[8].earnings = 800.0;
    
    strcpy(miners[9].minerID, "HOBBY_MINER_X");
    miners[9].hashRate = 5.3;
    miners[9].uptime = 120;
    miners[9].earnings = 400.0;
    
    minerCount = 10;
    
    printf("Loaded %d miners into the pool.\n", minerCount);
}

double calculateTotalPoolHashRate() {
    double total = 0.0;
    for (int i = 0; i < minerCount; i++) {
        total += miners[i].hashRate;
    }
    return total;
}

void calculateMinerRewards() {
    printf("\n=== CALCULATING MINER REWARDS ===\n");
    
    double totalHashRate = calculateTotalPoolHashRate();
    printf("Total Pool HashRate: %.2f TH/s\n", totalHashRate);
    printf("Daily Pool Reward: $%.2f\n", dailyPoolReward);
    
    printf("\nDetailed Reward Calculations:\n");
    printf("%-15s %8s %6s %10s %8s %8s %12s\n", 
           "Miner ID", "HashRate", "Uptime", "Base", "Bonus", "Penalty", "Final Reward");
    printf("---------------------------------------------------------------------------------\n");
    
    for (int i = 0; i < minerCount; i++) {
        // 1. Base reward calculation
        double baseReward = (miners[i].hashRate / totalHashRate) * dailyPoolReward;
        
        // 2. Uptime bonus (15% if uptime > 500 hours)
        double uptimeBonus = 0.0;
        if (miners[i].uptime > 500) {
            uptimeBonus = baseReward * (miners[i].uptime / 720.0) * 0.15;
        }
        
        // 3. Consistency bonus (10% - simplified assumption all qualify)
        double consistencyBonus = baseReward * 0.10;
        
        // 4. Penalty (-20% if uptime < 200 hours)
        double penalty = 0.0;
        if (miners[i].uptime < 200) {
            penalty = baseReward * 0.20;
        }
        
        // Calculate total bonuses and final reward
        double totalBonus = uptimeBonus + consistencyBonus;
        miners[i].finalReward = baseReward + totalBonus - penalty;
        
        // Calculate efficiency ratio
        miners[i].efficiency = miners[i].earnings / miners[i].hashRate;
        
        printf("%-15s %8.1f %6d %10.2f %8.2f %8.2f %12.2f\n",
               miners[i].minerID, miners[i].hashRate, miners[i].uptime,
               baseReward, totalBonus, penalty, miners[i].finalReward);
    }
}

void findTopEfficientMiners() {
    printf("\n=== TOP 3 MOST EFFICIENT MINERS ===\n");
    
    // Create a copy for sorting
    Miner sortedMiners[MAX_MINERS];
    for (int i = 0; i < minerCount; i++) {
        sortedMiners[i] = miners[i];
    }
    
    // Bubble sort by efficiency (descending)
    for (int i = 0; i < minerCount - 1; i++) {
        for (int j = 0; j < minerCount - i - 1; j++) {
            if (sortedMiners[j].efficiency < sortedMiners[j + 1].efficiency) {
                Miner temp = sortedMiners[j];
                sortedMiners[j] = sortedMiners[j + 1];
                sortedMiners[j + 1] = temp;
            }
        }
    }
    
    printf("Rank | Miner ID        | Efficiency ($/TH/s) | HashRate | Earnings\n");
    printf("-----|-----------------|--------------------|---------|---------\n");
    
    for (int i = 0; i < 3 && i < minerCount; i++) {
        printf(" %d   | %-15s | %18.2f | %8.1f | %8.2f\n",
               i + 1, sortedMiners[i].minerID, sortedMiners[i].efficiency,
               sortedMiners[i].hashRate, sortedMiners[i].earnings);
    }
    
    printf("\nEfficiency Analysis:\n");
    printf("- Most efficient miner: %s (%.2f $/TH/s)\n", 
           sortedMiners[0].minerID, sortedMiners[0].efficiency);
    printf("- Average pool efficiency: %.2f $/TH/s\n", 
           calculateTotalPoolHashRate() > 0 ? 
           (dailyPoolReward / calculateTotalPoolHashRate()) : 0);
}

void identifyWarningMiners() {
    printf("\n=== MINERS REQUIRING WARNINGS ===\n");
    
    int warningCount = 0;
    double avgHashRate = calculateTotalPoolHashRate() / minerCount;
    
    printf("Warning Criteria:\n");
    printf("- Uptime < 300 hours (out of 720 possible)\n");
    printf("- HashRate < %.1f TH/s (below average)\n", avgHashRate * 0.5);
    printf("- Efficiency < 100 $/TH/s\n\n");
    
    printf("Miners with Warnings:\n");
    printf("%-15s | Issues\n", "Miner ID");
    printf("----------------|--------------------------------------------------\n");
    
    for (int i = 0; i < minerCount; i++) {
        int hasWarning = 0;
        char warnings[200] = "";
        
        // Check uptime
        if (miners[i].uptime < 300) {
            strcat(warnings, "Low uptime");
            hasWarning = 1;
        }
        
        // Check hashrate (below 50% of average)
        if (miners[i].hashRate < avgHashRate * 0.5) {
            if (hasWarning) strcat(warnings, ", ");
            strcat(warnings, "Low hashrate");
            hasWarning = 1;
        }
        
        // Check efficiency
        if (miners[i].efficiency < 100.0) {
            if (hasWarning) strcat(warnings, ", ");
            strcat(warnings, "Low efficiency");
            hasWarning = 1;
        }
        
        if (hasWarning) {
            miners[i].warningFlag = 1;
            printf("%-15s | %s\n", miners[i].minerID, warnings);
            warningCount++;
        }
    }
    
    if (warningCount == 0) {
        printf("✅ All miners are performing adequately.\n");
    } else {
        printf("\nTotal miners with warnings: %d out of %d\n", warningCount, minerCount);
        printf("Recommendation: Contact warned miners for performance review.\n");
    }
}

void implementDynamicDifficultyAdjustment() {
    printf("\n=== DYNAMIC DIFFICULTY ADJUSTMENT ===\n");
    
    double totalHashRate = calculateTotalPoolHashRate();
    double targetBlockTime = 10.0; // minutes (Bitcoin standard)
    double currentBlockTime = 8.5; // simulated current time
    
    // Calculate difficulty adjustment
    double difficultyMultiplier = targetBlockTime / currentBlockTime;
    double networkDifficulty = 25000000000000.0; // Example current difficulty
    double newDifficulty = networkDifficulty * difficultyMultiplier;
    
    printf("Network Analysis:\n");
    printf("- Current total pool hashrate: %.2f TH/s\n", totalHashRate);
    printf("- Target block time: %.1f minutes\n", targetBlockTime);
    printf("- Current average block time: %.1f minutes\n", currentBlockTime);
    printf("- Current network difficulty: %.0f\n", networkDifficulty);
    
    printf("\nDifficulty Adjustment:\n");
    printf("- Adjustment multiplier: %.4f\n", difficultyMultiplier);
    printf("- Recommended new difficulty: %.0f\n", newDifficulty);
    
    if (difficultyMultiplier > 1.0) {
        printf("- Action: INCREASE difficulty (blocks found too quickly)\n");
    } else {
        printf("- Action: DECREASE difficulty (blocks found too slowly)\n");
    }
    
    // Pool strategy recommendation
    printf("\nPool Strategy Recommendation:\n");
    if (totalHashRate > 200.0) {
        printf("- Status: Large pool - Consider splitting for decentralization\n");
    } else if (totalHashRate > 100.0) {
        printf("- Status: Medium pool - Optimal size for consistent rewards\n");
    } else {
        printf("- Status: Small pool - Consider recruiting more miners\n");
    }
    
    // Estimated daily blocks
    double poolNetworkPercent = (totalHashRate / 150000.0) * 100; // Assume 150 PH/s network
    double estimatedDailyBlocks = 144 * (poolNetworkPercent / 100.0); // 144 blocks per day
    
    printf("- Pool network share: %.4f%%\n", poolNetworkPercent);
    printf("- Estimated blocks per day: %.2f\n", estimatedDailyBlocks);
    printf("- Estimated daily pool reward: $%.2f\n", estimatedDailyBlocks * 6.25 * 45000); // 6.25 BTC * $45k
}

void generatePoolReport() {
    printf("\n=== COMPREHENSIVE POOL REPORT ===\n");
    
    double totalHashRate = calculateTotalPoolHashRate();
    double totalEarnings = 0.0;
    double totalRewards = 0.0;
    int activeMiners = 0;
    
    for (int i = 0; i < minerCount; i++) {
        totalEarnings += miners[i].earnings;
        totalRewards += miners[i].finalReward;
        if (miners[i].uptime > 100) activeMiners++;
    }
    
    printf("Pool Performance Summary:\n");
    printf("- Total miners: %d\n", minerCount);
    printf("- Active miners (>100h uptime): %d\n", activeMiners);
    printf("- Total pool hashrate: %.2f TH/s\n", totalHashRate);
    printf("- Average hashrate per miner: %.2f TH/s\n", totalHashRate / minerCount);
    printf("- Total historical earnings: $%.2f\n", totalEarnings);
    printf("- Today's reward distribution: $%.2f\n", totalRewards);
    printf("- Pool efficiency: %.2f%%\n", (totalRewards / dailyPoolReward) * 100);
    
    // Performance categories
    int highPerformers = 0, mediumPerformers = 0, lowPerformers = 0;
    for (int i = 0; i < minerCount; i++) {
        if (miners[i].hashRate > 25.0 && miners[i].uptime > 600) {
            highPerformers++;
        } else if (miners[i].hashRate > 10.0 && miners[i].uptime > 400) {
            mediumPerformers++;
        } else {
            lowPerformers++;
        }
    }
    
    printf("\nMiner Categories:\n");
    printf("- High performers: %d miners\n", highPerformers);
    printf("- Medium performers: %d miners\n", mediumPerformers);
    printf("- Low performers: %d miners\n", lowPerformers);
}

int main() {
    printf("Cryptocurrency Mining Pool Management System\n");
    printf("=============================================\n");
    
    // Initialize miner data
    initializeMinerData();
    
    // Perform all calculations and analyses
    calculateMinerRewards();
    findTopEfficientMiners();
    identifyWarningMiners();
    implementDynamicDifficultyAdjustment();
    generatePoolReport();
    
    printf("\n=============================================\n");
    printf("Mining pool analysis completed successfully!\n");
    printf("=============================================\n");
    
    return 0;
}
