/*
===============================================================================
Programming Fundamentals - Mid Term Exam III
Advanced Critical Thinking Assessment
Total Time: 2 Hours | Total Marks: 50
===============================================================================
*/

/* 
QUESTION 1: Smart Traffic Management System [10 Marks, 25 mins]
===============================================================================
You are developing a smart traffic control system for Lahore's main intersections.
The system uses a 3D array to represent traffic data: traffic[4][4][24] where:
- First dimension: 4 intersections (0-3)  
- Second dimension: 4 directions (North=0, South=1, East=2, West=3)
- Third dimension: 24 hours of the day

Each cell contains the vehicle count for that intersection, direction, and hour.

REQUIREMENTS:
a) Find the "Rush Hour" - the hour when total city-wide traffic is maximum
b) Identify the "Critical Intersection" - intersection with highest average daily traffic
c) Determine "Congestion Pattern" - which direction has most consistent traffic 
   (lowest standard deviation across all intersections and hours)
d) Implement "Load Balancing" - redistribute traffic by suggesting alternate routes
   when any intersection-direction exceeds 150 vehicles/hour

HINT: You'll need to calculate sums, averages, and standard deviation across 
different dimensions of the 3D array. Think about nested loops and mathematical formulas.
*/

/* 
QUESTION 2: Cryptocurrency Mining Pool [10 Marks, 25 mins]
===============================================================================
A cryptocurrency mining pool tracks miners' contributions using parallel arrays:
- char minerIDs[100][20];     // Miner identification
- double hashRates[100];      // Hashing power in TH/s
- int uptime[100];           // Hours online in last 30 days  
- double earnings[100];      // Total earnings in last 30 days

The pool uses a complex reward distribution algorithm:
1. Base reward = (Individual HashRate / Total Pool HashRate) × Daily Pool Reward
2. Uptime bonus = Base reward × (uptime/720) × 0.15 if uptime > 500 hours
3. Consistency bonus = Base reward × 0.10 if standard deviation of daily hash < 5%
4. Penalty = -20% if uptime < 200 hours

REQUIREMENTS:
a) Calculate each miner's final reward for the day (Daily Pool Reward = $50,000)
b) Identify top 3 most efficient miners (highest earnings per TH/s ratio)
c) Find miners who should be warned (uptime < 300 hours or hashrate declining)
d) Implement dynamic difficulty adjustment based on pool's total hashrate

HINT: You'll need statistical calculations, conditional logic for bonuses/penalties,
and sorting algorithms. Consider efficiency metrics and trend analysis.
*/

/* 
QUESTION 3: DNA Sequence Analysis Engine [10 Marks, 25 mins]
===============================================================================
A bioinformatics lab needs a program to analyze DNA sequences for genetic research.
DNA sequences are stored as strings containing only 'A', 'T', 'G', 'C' characters.

The program must implement these advanced algorithms:
1. Pattern Matching: Find all occurrences of a subsequence (e.g., "ATGC" in main sequence)
2. Complementary Strand: Generate complement where A↔T and G↔C, then reverse it
3. Reading Frame Analysis: Check all 6 possible reading frames (3 forward, 3 reverse)
4. Mutation Detection: Compare two sequences and identify insertion, deletion, substitution

CRITICAL THINKING CHALLENGE:
The DNA sequence can be up to 10,000 characters long. Your algorithm must be efficient.
A naive approach would be O(n²) for pattern matching - can you optimize it?

REQUIREMENTS:
a) Implement efficient pattern matching (hint: use KMP algorithm concepts)
b) Generate complement and find palindromic sequences
c) Detect Open Reading Frames (sequences between start codon "ATG" and stop codons)
d) Calculate sequence similarity percentage between two DNA strings

HINT: String manipulation, efficient searching algorithms, and biological knowledge
of DNA structure. Think about optimization techniques for large datasets.
*/

/* 
QUESTION 4: Advanced Memory Pool Manager [10 Marks, 30 mins]  
===============================================================================
Design a custom memory pool manager that simulates dynamic memory allocation
using a large static array. This tests your understanding of pointers, memory
management, and data structures.

You have a memory pool: char memoryPool[10000];
You must implement these functions using only this array:

void* myMalloc(size_t size);     // Allocate memory block
void myFree(void* ptr);          // Deallocate memory block  
void defragment();               // Defragment memory pool
void printMemoryMap();           // Show memory layout

ADVANCED REQUIREMENTS:
a) Handle memory fragmentation efficiently
b) Implement a "buddy system" for power-of-2 sized allocations
c) Track allocated blocks using a metadata structure within the pool
d) Detect memory leaks and double-free errors
e) Implement garbage collection when fragmentation exceeds 30%

CRITICAL CHALLENGE:
Your metadata must also be stored within the memoryPool array. Design a header
structure for each allocated block that tracks size, status, and linking information.

HINT: This requires deep understanding of memory layout, pointer arithmetic,
linked lists, and algorithms. Think about how real memory allocators work.
*/

/* 
QUESTION 5: Real-time Stock Trading Algorithm [10 Marks, 30 mins]
===============================================================================
Develop a high-frequency trading algorithm that processes real-time stock data
and makes buy/sell decisions. The system receives price updates every millisecond
and must make instant decisions.

Data structures:
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
} Position;

ALGORITHM REQUIREMENTS:
a) Moving Average Crossover: Buy when 5-period MA crosses above 20-period MA
b) RSI Strategy: Buy when RSI < 30 (oversold), sell when RSI > 70 (overbought)  
c) Volume Analysis: Only trade when current volume > 1.5× average volume
d) Risk Management: Never risk more than 2% of portfolio on single trade
e) Portfolio Rebalancing: Maintain maximum 10 positions simultaneously

CRITICAL THINKING ELEMENTS:
- Handle real-time data streams efficiently (circular buffers)
- Implement technical indicators (MA, RSI, Bollinger Bands)
- Risk management and position sizing
- Performance optimization for microsecond-level decisions

HINT: This combines data structures, statistical calculations, financial algorithms,
and real-time processing. Focus on efficiency and accuracy.
*/

/*
===============================================================================
SOLUTIONS AND HINTS
===============================================================================

QUESTION 1 SOLUTION APPROACH:
- Use nested loops to traverse 3D array
- Calculate totals using accumulator variables  
- Standard deviation formula: σ = √(Σ(x-μ)²/n)
- Use sorting to find maximum/minimum values
- Implement threshold checking for load balancing

QUESTION 2 SOLUTION APPROACH:
- Calculate pool totals first, then individual percentages
- Use conditional statements for bonus/penalty logic
- Implement sorting algorithm for efficiency ranking
- Track trends using historical data comparison
- Dynamic difficulty = f(total_hashrate, target_time)

QUESTION 3 SOLUTION APPROACH:  
- KMP algorithm for efficient pattern matching
- Use character mapping for complement generation
- Sliding window technique for reading frames
- Dynamic programming for sequence alignment
- Edit distance algorithm for mutation detection

QUESTION 4 SOLUTION APPROACH:
- Design block header: [size|status|next_ptr]
- Use free list for available blocks
- Implement first-fit or best-fit allocation
- Coalescing algorithm for defragmentation
- Buddy system using power-of-2 mathematics

QUESTION 5 SOLUTION APPROACH:
- Circular buffer for price history
- Technical indicators: MA = Σ(prices)/n, RSI = 100 - (100/(1+RS))
- Position sizing: risk_amount = portfolio_value × 0.02
- Priority queue for stop-loss/take-profit orders
- Hash table for O(1) symbol lookup
*/

int main(void) {
    printf("Programming Fundamentals - Advanced Critical Thinking Assessment\n");
    printf("Choose a question to implement (1-5): ");
    
    // Student implementation space
    
    return 0;
}
