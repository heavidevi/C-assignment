/*
===============================================================================
QUESTION 1 SOLUTION: Smart Traffic Management System
Programming Fundamentals - Mid Term Exam III
===============================================================================
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

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

void initializeTrafficData() {
    printf("Initializing traffic data with realistic patterns...\n");
    srand(time(NULL));
    
    for (int intersection = 0; intersection < 4; intersection++) {
        for (int direction = 0; direction < 4; direction++) {
            for (int hour = 0; hour < 24; hour++) {
                // Create realistic traffic patterns
                int baseTraffic = 20;
                
                // Rush hour peaks (7-9 AM and 5-7 PM)
                if ((hour >= 7 && hour <= 9) || (hour >= 17 && hour <= 19)) {
                    baseTraffic = 80 + rand() % 100;
                }
                // Moderate traffic (10 AM - 4 PM)
                else if (hour >= 10 && hour <= 16) {
                    baseTraffic = 40 + rand() % 60;
                }
                // Light traffic (night hours)
                else if (hour >= 22 || hour <= 5) {
                    baseTraffic = 5 + rand() % 25;
                }
                // Normal traffic
                else {
                    baseTraffic = 30 + rand() % 50;
                }
                
                traffic[intersection][direction][hour] = baseTraffic;
            }
        }
    }
}

void findRushHour() {
    printf("\n=== FINDING RUSH HOUR ===\n");
    
    int hourlyTotals[24] = {0};
    int maxTraffic = 0, rushHour = 0;
    
    // Calculate total traffic for each hour
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
    
    printf("Rush Hour Analysis:\n");
    printf("Peak traffic hour: %02d:00 with %d total vehicles\n", rushHour, maxTraffic);
    
    // Show top 5 busiest hours
    printf("\nTop 5 Busiest Hours:\n");
    printf("Hour  | Total Vehicles\n");
    printf("------|---------------\n");
    
    // Simple sorting to find top 5
    for (int rank = 0; rank < 5; rank++) {
        int maxIdx = 0;
        for (int i = 1; i < 24; i++) {
            if (hourlyTotals[i] > hourlyTotals[maxIdx]) {
                maxIdx = i;
            }
        }
        printf("%02d:00 | %d\n", maxIdx, hourlyTotals[maxIdx]);
        hourlyTotals[maxIdx] = -1; // Mark as processed
    }
}

void findCriticalIntersection() {
    printf("\n=== FINDING CRITICAL INTERSECTION ===\n");
    
    double intersectionAverages[4] = {0};
    int criticalIntersection = 0;
    double maxAverage = 0;
    
    for (int intersection = 0; intersection < 4; intersection++) {
        int total = 0;
        
        // Calculate total traffic for this intersection
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
    
    printf("Critical Intersection Analysis:\n");
    printf("Most critical intersection: Intersection %d\n", criticalIntersection);
    printf("Average vehicles per hour per direction: %.2f\n", maxAverage);
    
    printf("\nAll Intersection Averages:\n");
    printf("Intersection | Avg Vehicles/Hour/Direction\n");
    printf("-------------|---------------------------\n");
    
    for (int i = 0; i < 4; i++) {
        printf("     %d       |           %.2f\n", i, intersectionAverages[i]);
    }
}

void analyzeCongestionPattern() {
    printf("\n=== ANALYZING CONGESTION PATTERNS ===\n");
    
    const char* directions[] = {"North", "South", "East", "West"};
    double minStdDev = 999999.0;
    int consistentDirection = 0;
    
    for (int direction = 0; direction < 4; direction++) {
        int directionData[96]; // 4 intersections × 24 hours
        int index = 0;
        
        // Collect all data for this direction
        for (int intersection = 0; intersection < 4; intersection++) {
            for (int hour = 0; hour < 24; hour++) {
                directionData[index++] = traffic[intersection][direction][hour];
            }
        }
        
        double stdDev = calculateStandardDeviation(directionData, 96);
        
        printf("%s direction - Standard Deviation: %.2f\n", directions[direction], stdDev);
        
        if (stdDev < minStdDev) {
            minStdDev = stdDev;
            consistentDirection = direction;
        }
    }
    
    printf("\nMost Consistent Traffic Pattern:\n");
    printf("Direction: %s (Standard Deviation: %.2f)\n", 
           directions[consistentDirection], minStdDev);
    printf("This direction has the most predictable traffic flow.\n");
}

void implementLoadBalancing() {
    printf("\n=== LOAD BALANCING ANALYSIS ===\n");
    
    const char* directions[] = {"North", "South", "East", "West"};
    int alertCount = 0;
    int threshold = 150;
    
    printf("Checking for overloaded routes (threshold: %d vehicles/hour)...\n\n", threshold);
    
    for (int intersection = 0; intersection < 4; intersection++) {
        for (int direction = 0; direction < 4; direction++) {
            for (int hour = 0; hour < 24; hour++) {
                if (traffic[intersection][direction][hour] > threshold) {
                    printf("🚨 ALERT: Intersection %d, %s direction, %02d:00 - %d vehicles\n",
                           intersection, directions[direction], hour, 
                           traffic[intersection][direction][hour]);
                    
                    // Suggest alternate routes
                    printf("   💡 Suggested Actions:\n");
                    printf("   - Redirect traffic to adjacent intersections\n");
                    printf("   - Extend green light duration for this direction\n");
                    printf("   - Deploy traffic officers for manual control\n\n");
                    
                    alertCount++;
                }
            }
        }
    }
    
    if (alertCount == 0) {
        printf("✅ No overloaded routes detected. Traffic flow is within normal limits.\n");
    } else {
        printf("Total alerts generated: %d\n", alertCount);
        printf("Recommendation: Implement dynamic traffic signal control.\n");
    }
}

void generateTrafficReport() {
    printf("\n=== COMPREHENSIVE TRAFFIC REPORT ===\n");
    
    // Calculate city-wide statistics
    int totalCityTraffic = 0;
    int peakHourTraffic = 0;
    int nightTraffic = 0;
    
    for (int intersection = 0; intersection < 4; intersection++) {
        for (int direction = 0; direction < 4; direction++) {
            for (int hour = 0; hour < 24; hour++) {
                int vehicles = traffic[intersection][direction][hour];
                totalCityTraffic += vehicles;
                
                // Peak hours: 7-9 AM, 5-7 PM
                if ((hour >= 7 && hour <= 9) || (hour >= 17 && hour <= 19)) {
                    peakHourTraffic += vehicles;
                }
                
                // Night hours: 10 PM - 6 AM
                if (hour >= 22 || hour <= 6) {
                    nightTraffic += vehicles;
                }
            }
        }
    }
    
    printf("City-wide Traffic Statistics:\n");
    printf("- Total daily vehicles: %d\n", totalCityTraffic);
    printf("- Average vehicles per hour: %.2f\n", totalCityTraffic / 24.0);
    printf("- Peak hours traffic: %d (%.1f%% of total)\n", 
           peakHourTraffic, (peakHourTraffic * 100.0) / totalCityTraffic);
    printf("- Night hours traffic: %d (%.1f%% of total)\n", 
           nightTraffic, (nightTraffic * 100.0) / totalCityTraffic);
    
    // Traffic efficiency score
    double efficiencyScore = 100.0 - ((peakHourTraffic * 100.0) / totalCityTraffic - 25.0);
    if (efficiencyScore > 100) efficiencyScore = 100;
    if (efficiencyScore < 0) efficiencyScore = 0;
    
    printf("- Traffic Distribution Efficiency: %.1f%%\n", efficiencyScore);
}

int main() {
    printf("Smart Traffic Management System for Lahore\n");
    printf("==========================================\n");
    
    // Initialize traffic data
    initializeTrafficData();
    
    // Perform all analyses
    findRushHour();
    findCriticalIntersection();
    analyzeCongestionPattern();
    implementLoadBalancing();
    generateTrafficReport();
    
    printf("\n==========================================\n");
    printf("Traffic analysis completed successfully!\n");
    printf("==========================================\n");
    
    return 0;
}
