/*
===============================================================================
QUESTION 5 SOLUTION: Real-time Stock Trading Algorithm
Programming Fundamentals - Mid Term Exam III
===============================================================================
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>

#define MAX_POSITIONS 10
#define PRICE_HISTORY_SIZE 100
#define MAX_SYMBOLS 20

// Data structures from the question
typedef struct {
    char symbol[10];      // Stock symbol (e.g., "AAPL")
    double price;         // Current price
    long long timestamp;  // Unix timestamp in milliseconds
    int volume;          // Trading volume
} StockData;

typedef struct {
    char symbol[10];
    double buyPrice;
    int quantity;
    long long buyTime;
    double stopLoss;     // Automatic sell if price drops below this
    double takeProfit;   // Automatic sell if price rises above this
    double currentValue; // Current position value
    double profitLoss;   // Unrealized P&L
} Position;

// Advanced trading data structure
typedef struct {
    StockData priceHistory[PRICE_HISTORY_SIZE];
    int historyIndex;    // Circular buffer index
    int historyCount;    // Number of data points
    double ma5, ma20;    // Moving averages
    double rsi;          // Relative Strength Index
    double avgVolume;    // Average volume
    double volatility;   // Price volatility
    double momentum;     // Price momentum
} TradingData;

// Global trading system variables
Position portfolio[MAX_POSITIONS];
int portfolioSize = 0;
double portfolioValue = 100000.0; // $100K starting capital
double totalReturns = 0.0;
int totalTrades = 0;
int winningTrades = 0;

// Function prototypes
void initializeTradingData();
void updateTechnicalIndicators(TradingData* data);
void calculateMovingAverages(TradingData* data);
void calculateRSI(TradingData* data);
void calculateVolatility(TradingData* data);
int generateBuySignal(TradingData* data, StockData* current);
int generateSellSignal(Position* pos, StockData* current, TradingData* data);
void executeOrder(char* symbol, double price, int quantity, char* action);
void updatePortfolio(StockData* marketData, TradingData* tradingData);
void performRiskManagement();
void displayTradingDashboard();
void generateTradingReport();

// Sample market data for multiple stocks
TradingData stockData[5];
char symbols[5][10] = {"AAPL", "MSFT", "GOOGL", "TSLA", "AMZN"};

void initializeTradingData() {
    printf("Initializing real-time trading system...\n");
    
    srand(time(NULL));
    
    // Initialize trading data for each stock
    for (int stock = 0; stock < 5; stock++) {
        TradingData* data = &stockData[stock];
        data->historyIndex = 0;
        data->historyCount = 0;
        
        // Generate realistic price history
        double basePrice = 100.0 + (stock * 50); // Different base prices
        
        for (int i = 0; i < 50; i++) {
            // Simulate price movement with some randomness
            double priceChange = (rand() % 201 - 100) / 100.0; // -1 to +1
            double newPrice = basePrice + (priceChange * (i + 1) * 0.1);
            
            strcpy(data->priceHistory[i].symbol, symbols[stock]);
            data->priceHistory[i].price = newPrice;
            data->priceHistory[i].timestamp = time(NULL) - (50 - i) * 300; // 5-minute intervals
            data->priceHistory[i].volume = 1000000 + rand() % 2000000; // 1-3M volume
            
            data->historyIndex = (i + 1) % PRICE_HISTORY_SIZE;
            data->historyCount = i + 1;
        }
        
        // Calculate initial technical indicators
        updateTechnicalIndicators(data);
    }
    
    printf("Trading system initialized with %d stocks\n", 5);
}

void calculateMovingAverages(TradingData* data) {
    if (data->historyCount < 5) return;
    
    // Calculate 5-period MA
    double sum5 = 0;
    for (int i = 0; i < 5 && i < data->historyCount; i++) {
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

void calculateRSI(TradingData* data) {
    if (data->historyCount < 15) return;
    
    double gains = 0, losses = 0;
    
    // Calculate average gains and losses over 14 periods
    for (int i = 1; i < 15 && i < data->historyCount; i++) {
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

void calculateVolatility(TradingData* data) {
    if (data->historyCount < 10) return;
    
    // Calculate price volatility (standard deviation of returns)
    double returns[20];
    int returnCount = 0;
    
    for (int i = 1; i < 20 && i < data->historyCount; i++) {
        int currIndex = (data->historyIndex - 1 - i + PRICE_HISTORY_SIZE) % PRICE_HISTORY_SIZE;
        int prevIndex = (currIndex - 1 + PRICE_HISTORY_SIZE) % PRICE_HISTORY_SIZE;
        
        double return_pct = (data->priceHistory[currIndex].price - data->priceHistory[prevIndex].price) / 
                           data->priceHistory[prevIndex].price;
        returns[returnCount++] = return_pct;
    }
    
    // Calculate standard deviation
    double mean = 0;
    for (int i = 0; i < returnCount; i++) {
        mean += returns[i];
    }
    mean /= returnCount;
    
    double variance = 0;
    for (int i = 0; i < returnCount; i++) {
        variance += pow(returns[i] - mean, 2);
    }
    variance /= returnCount;
    
    data->volatility = sqrt(variance) * 100.0; // Convert to percentage
}

void updateTechnicalIndicators(TradingData* data) {
    // Calculate average volume
    long long totalVolume = 0;
    int volumeCount = data->historyCount > 20 ? 20 : data->historyCount;
    
    for (int i = 0; i < volumeCount; i++) {
        int index = (data->historyIndex - 1 - i + PRICE_HISTORY_SIZE) % PRICE_HISTORY_SIZE;
        totalVolume += data->priceHistory[index].volume;
    }
    data->avgVolume = totalVolume / volumeCount;
    
    // Update all indicators
    calculateMovingAverages(data);
    calculateRSI(data);
    calculateVolatility(data);
    
    // Calculate momentum (rate of change over 10 periods)
    if (data->historyCount >= 10) {
        int currentIndex = (data->historyIndex - 1 + PRICE_HISTORY_SIZE) % PRICE_HISTORY_SIZE;
        int pastIndex = (data->historyIndex - 10 + PRICE_HISTORY_SIZE) % PRICE_HISTORY_SIZE;
        
        double currentPrice = data->priceHistory[currentIndex].price;
        double pastPrice = data->priceHistory[pastIndex].price;
        
        data->momentum = ((currentPrice - pastPrice) / pastPrice) * 100.0;
    }
}

int generateBuySignal(TradingData* data, StockData* current) {
    // Check all conditions for buy signal
    
    // 1. Moving Average Crossover: 5-period MA > 20-period MA
    int maCrossover = (data->historyCount >= 20) && (data->ma5 > data->ma20);
    
    // 2. RSI Oversold: RSI < 30
    int rsiOversold = (data->historyCount >= 15) && (data->rsi < 30);
    
    // 3. Volume Analysis: Current volume > 1.5x average
    int highVolume = (current->volume > data->avgVolume * 1.5);
    
    // 4. Positive momentum
    int positiveMomentum = (data->momentum > 0);
    
    // 5. Portfolio space available
    int portfolioSpace = (portfolioSize < MAX_POSITIONS);
    
    // 6. Low volatility (stable stock)
    int lowVolatility = (data->volatility < 5.0);
    
    // Generate signal if at least 4 out of 6 conditions are met
    int signalStrength = maCrossover + rsiOversold + highVolume + 
                        positiveMomentum + portfolioSpace + lowVolatility;
    
    return signalStrength >= 4;
}

int generateSellSignal(Position* pos, StockData* current, TradingData* data) {
    // 1. Stop loss triggered
    if (current->price <= pos->stopLoss) {
        return 1;
    }
    
    // 2. Take profit triggered
    if (current->price >= pos->takeProfit) {
        return 1;
    }
    
    // 3. RSI Overbought (RSI > 70)
    if (data->rsi > 70) {
        return 1;
    }
    
    // 4. Moving average reversal (MA5 < MA20)
    if (data->ma5 < data->ma20) {
        return 1;
    }
    
    // 5. High volatility (risky conditions)
    if (data->volatility > 8.0) {
        return 1;
    }
    
    return 0;
}

void executeOrder(char* symbol, double price, int quantity, char* action) {
    printf("📈 EXECUTING ORDER:\n");
    printf("   Action: %s\n", action);
    printf("   Symbol: %s\n", symbol);
    printf("   Price: $%.2f\n", price);
    printf("   Quantity: %d shares\n", quantity);
    printf("   Total Value: $%.2f\n", price * quantity);
    
    if (strcmp(action, "BUY") == 0) {
        if (portfolioSize < MAX_POSITIONS) {
            // Add new position
            strcpy(portfolio[portfolioSize].symbol, symbol);
            portfolio[portfolioSize].buyPrice = price;
            portfolio[portfolioSize].quantity = quantity;
            portfolio[portfolioSize].buyTime = time(NULL);
            portfolio[portfolioSize].stopLoss = price * 0.95; // 5% stop loss
            portfolio[portfolioSize].takeProfit = price * 1.15; // 15% take profit
            portfolio[portfolioSize].currentValue = price * quantity;
            portfolio[portfolioSize].profitLoss = 0.0;
            
            portfolioSize++;
            totalTrades++;
            
            printf("   ✅ Position added to portfolio\n");
        }
    } else if (strcmp(action, "SELL") == 0) {
        // Find and remove position
        for (int i = 0; i < portfolioSize; i++) {
            if (strcmp(portfolio[i].symbol, symbol) == 0) {
                double profit = (price - portfolio[i].buyPrice) * portfolio[i].quantity;
                totalReturns += profit;
                
                if (profit > 0) {
                    winningTrades++;
                    printf("   💰 Profit: $%.2f\n", profit);
                } else {
                    printf("   📉 Loss: $%.2f\n", profit);
                }
                
                // Remove position (shift array)
                for (int j = i; j < portfolioSize - 1; j++) {
                    portfolio[j] = portfolio[j + 1];
                }
                portfolioSize--;
                break;
            }
        }
    }
    
    printf("\n");
}

void updatePortfolio(StockData* marketData, TradingData* tradingData) {
    // Update current values and P&L for all positions
    for (int i = 0; i < portfolioSize; i++) {
        // Find matching market data
        for (int j = 0; j < 5; j++) {
            if (strcmp(portfolio[i].symbol, marketData[j].symbol) == 0) {
                portfolio[i].currentValue = marketData[j].price * portfolio[i].quantity;
                portfolio[i].profitLoss = (marketData[j].price - portfolio[i].buyPrice) * portfolio[i].quantity;
                break;
            }
        }
    }
}

void performRiskManagement() {
    printf("=== RISK MANAGEMENT ANALYSIS ===\n");
    
    double totalExposure = 0.0;
    double totalUnrealizedPL = 0.0;
    int riskAlerts = 0;
    
    for (int i = 0; i < portfolioSize; i++) {
        totalExposure += portfolio[i].currentValue;
        totalUnrealizedPL += portfolio[i].profitLoss;
        
        // Check risk levels
        double positionRisk = (portfolio[i].currentValue / portfolioValue) * 100.0;
        if (positionRisk > 10.0) { // More than 10% of portfolio in one position
            printf("⚠️  HIGH RISK: %s position is %.1f%% of portfolio\n", 
                   portfolio[i].symbol, positionRisk);
            riskAlerts++;
        }
        
        // Check unrealized losses
        double lossPercent = (portfolio[i].profitLoss / (portfolio[i].buyPrice * portfolio[i].quantity)) * 100.0;
        if (lossPercent < -8.0) { // More than 8% loss
            printf("🚨 LARGE LOSS: %s down %.1f%% (consider selling)\n", 
                   portfolio[i].symbol, lossPercent);
            riskAlerts++;
        }
    }
    
    double exposurePercent = (totalExposure / portfolioValue) * 100.0;
    
    printf("\nRisk Metrics:\n");
    printf("- Total market exposure: $%.2f (%.1f%% of portfolio)\n", totalExposure, exposurePercent);
    printf("- Unrealized P&L: $%.2f\n", totalUnrealizedPL);
    printf("- Risk alerts: %d\n", riskAlerts);
    printf("- Portfolio utilization: %.1f%%\n", exposurePercent);
    
    if (exposurePercent > 90.0) {
        printf("⚠️  WARNING: Portfolio is highly leveraged!\n");
    }
    
    if (riskAlerts == 0) {
        printf("✅ Risk levels are within acceptable limits\n");
    }
    
    printf("\n");
}

void displayTradingDashboard() {
    printf("=== REAL-TIME TRADING DASHBOARD ===\n");
    
    // Display current positions
    if (portfolioSize > 0) {
        printf("Active Positions:\n");
        printf("%-6s | %8s | %6s | %10s | %10s | %8s | %10s\n",
               "Symbol", "Buy Price", "Qty", "Current", "Value", "P&L", "P&L %");
        printf("-------|----------|--------|-----------|-----------|----------|----------\n");
        
        double totalValue = 0.0, totalPL = 0.0;
        
        for (int i = 0; i < portfolioSize; i++) {
            double plPercent = (portfolio[i].profitLoss / (portfolio[i].buyPrice * portfolio[i].quantity)) * 100.0;
            double currentPrice = portfolio[i].currentValue / portfolio[i].quantity;
            
            printf("%-6s | %8.2f | %6d | %10.2f | %10.2f | %8.2f | %9.1f%%\n",
                   portfolio[i].symbol,
                   portfolio[i].buyPrice,
                   portfolio[i].quantity,
                   currentPrice,
                   portfolio[i].currentValue,
                   portfolio[i].profitLoss,
                   plPercent);
            
            totalValue += portfolio[i].currentValue;
            totalPL += portfolio[i].profitLoss;
        }
        
        printf("-------|----------|--------|-----------|-----------|----------|----------\n");
        printf("TOTAL  |          |        |           | %10.2f | %8.2f | %9.1f%%\n",
               totalValue, totalPL, (totalPL / totalValue) * 100.0);
    } else {
        printf("No active positions\n");
    }
    
    printf("\n");
}

void simulateRealTimeTrading() {
    printf("=== REAL-TIME TRADING SIMULATION ===\n");
    
    // Simulate 10 trading cycles
    for (int cycle = 0; cycle < 10; cycle++) {
        printf("--- Trading Cycle %d ---\n", cycle + 1);
        
        // Update market data
        StockData currentMarket[5];
        for (int i = 0; i < 5; i++) {
            TradingData* data = &stockData[i];
            
            // Simulate new price data
            int lastIndex = (data->historyIndex - 1 + PRICE_HISTORY_SIZE) % PRICE_HISTORY_SIZE;
            double lastPrice = data->priceHistory[lastIndex].price;
            double priceChange = (rand() % 201 - 100) / 1000.0; // -0.1 to +0.1
            double newPrice = lastPrice * (1.0 + priceChange);
            
            // Add new data point
            strcpy(data->priceHistory[data->historyIndex].symbol, symbols[i]);
            data->priceHistory[data->historyIndex].price = newPrice;
            data->priceHistory[data->historyIndex].timestamp = time(NULL);
            data->priceHistory[data->historyIndex].volume = data->avgVolume + (rand() % 1000000 - 500000);
            
            data->historyIndex = (data->historyIndex + 1) % PRICE_HISTORY_SIZE;
            if (data->historyCount < PRICE_HISTORY_SIZE) data->historyCount++;
            
            // Update technical indicators
            updateTechnicalIndicators(data);
            
            // Store current market data
            currentMarket[i] = data->priceHistory[(data->historyIndex - 1 + PRICE_HISTORY_SIZE) % PRICE_HISTORY_SIZE];
            
            printf("%s: $%.2f (MA5: %.2f, MA20: %.2f, RSI: %.1f, Vol: %.1f%%)\n",
                   symbols[i], newPrice, data->ma5, data->ma20, data->rsi, data->volatility);
        }
        
        // Update portfolio with current prices
        updatePortfolio(currentMarket, stockData);
        
        // Check for trading signals
        for (int i = 0; i < 5; i++) {
            // Check buy signals
            if (generateBuySignal(&stockData[i], &currentMarket[i])) {
                // Calculate position size (2% risk rule)
                double riskAmount = portfolioValue * 0.02;
                int quantity = (int)(riskAmount / (currentMarket[i].price * 0.05)); // 5% stop loss
                
                if (quantity > 0) {
                    executeOrder(symbols[i], currentMarket[i].price, quantity, "BUY");
                }
            }
            
            // Check sell signals for existing positions
            for (int j = 0; j < portfolioSize; j++) {
                if (strcmp(portfolio[j].symbol, symbols[i]) == 0) {
                    if (generateSellSignal(&portfolio[j], &currentMarket[i], &stockData[i])) {
                        executeOrder(symbols[i], currentMarket[i].price, portfolio[j].quantity, "SELL");
                        break; // Position was removed, break inner loop
                    }
                }
            }
        }
        
        printf("\n");
    }
}

void generateTradingReport() {
    printf("=== COMPREHENSIVE TRADING REPORT ===\n");
    
    double winRate = totalTrades > 0 ? (double)winningTrades / totalTrades * 100.0 : 0.0;
    double avgReturn = totalTrades > 0 ? totalReturns / totalTrades : 0.0;
    
    printf("Performance Summary:\n");
    printf("- Total trades executed: %d\n", totalTrades);
    printf("- Winning trades: %d\n", winningTrades);
    printf("- Losing trades: %d\n", totalTrades - winningTrades);
    printf("- Win rate: %.1f%%\n", winRate);
    printf("- Total returns: $%.2f\n", totalReturns);
    printf("- Average return per trade: $%.2f\n", avgReturn);
    printf("- Return on capital: %.2f%%\n", (totalReturns / portfolioValue) * 100.0);
    
    // Calculate Sharpe ratio (simplified)
    double sharpeRatio = avgReturn > 0 ? avgReturn / (avgReturn * 0.3) : 0; // Simplified calculation
    printf("- Sharpe ratio: %.2f\n", sharpeRatio);
    
    printf("\nTechnical Analysis Summary:\n");
    for (int i = 0; i < 5; i++) {
        TradingData* data = &stockData[i];
        int lastIndex = (data->historyIndex - 1 + PRICE_HISTORY_SIZE) % PRICE_HISTORY_SIZE;
        double currentPrice = data->priceHistory[lastIndex].price;
        
        printf("- %s: $%.2f | Trend: %s | RSI: %.1f | Volatility: %.1f%%\n",
               symbols[i], currentPrice,
               (data->ma5 > data->ma20) ? "Bullish" : "Bearish",
               data->rsi, data->volatility);
    }
    
    printf("\nAlgorithm Performance:\n");
    if (winRate > 60.0) {
        printf("✅ EXCELLENT: High win rate algorithm\n");
    } else if (winRate > 40.0) {
        printf("✅ GOOD: Decent performance\n");
    } else {
        printf("⚠️  NEEDS IMPROVEMENT: Low win rate\n");
    }
    
    if (totalReturns > 0) {
        printf("✅ PROFITABLE: Positive returns achieved\n");
    } else {
        printf("📉 UNPROFITABLE: Strategy needs optimization\n");
    }
}

int main() {
    printf("Real-time Stock Trading Algorithm\n");
    printf("=================================\n");
    
    // Initialize trading system
    initializeTradingData();
    
    // Display initial technical indicators
    printf("\nInitial Technical Analysis:\n");
    for (int i = 0; i < 5; i++) {
        TradingData* data = &stockData[i];
        int lastIndex = (data->historyIndex - 1 + PRICE_HISTORY_SIZE) % PRICE_HISTORY_SIZE;
        double currentPrice = data->priceHistory[lastIndex].price;
        
        printf("%s: $%.2f | MA5: %.2f | MA20: %.2f | RSI: %.1f | Momentum: %.1f%%\n",
               symbols[i], currentPrice, data->ma5, data->ma20, data->rsi, data->momentum);
    }
    
    // Simulate real-time trading
    simulateRealTimeTrading();
    
    // Display final portfolio
    displayTradingDashboard();
    
    // Perform risk analysis
    performRiskManagement();
    
    // Generate comprehensive report
    generateTradingReport();
    
    printf("\n=================================\n");
    printf("Trading simulation completed!\n");
    printf("=================================\n");
    
    return 0;
}
