/*
===============================================================================
QUESTION 4 SOLUTION: Advanced Memory Pool Manager
Programming Fundamentals - Mid Term Exam III
===============================================================================
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#define POOL_SIZE 10000
#define MIN_BLOCK_SIZE 16
#define ALIGNMENT 8

// Block header structure for managing memory blocks
typedef struct BlockHeader {
    size_t size;                    // Size of the block (excluding header)
    int isFree;                     // 1 if free, 0 if allocated
    struct BlockHeader* next;       // Pointer to next block
    struct BlockHeader* prev;       // Pointer to previous block
    unsigned int magic;             // Magic number for corruption detection
} BlockHeader;

#define MAGIC_FREE 0xDEADBEEF
#define MAGIC_ALLOCATED 0xBEEFDEAD

// Global memory pool and management variables
char memoryPool[POOL_SIZE];
BlockHeader* poolStart = NULL;
int isInitialized = 0;
int totalAllocations = 0;
int totalDeallocations = 0;
size_t totalBytesAllocated = 0;
size_t totalBytesFreed = 0;

// Function prototypes
void initializeMemoryPool();
void* myMalloc(size_t size);
void myFree(void* ptr);
void defragment();
void printMemoryMap();
double calculateFragmentation();
int detectMemoryLeaks();
void buddySystemAlloc();
void garbageCollection();

// Utility functions
size_t alignSize(size_t size) {
    return (size + ALIGNMENT - 1) & ~(ALIGNMENT - 1);
}

int isPowerOfTwo(size_t size) {
    return size && !(size & (size - 1));
}

size_t nextPowerOfTwo(size_t size) {
    size--;
    size |= size >> 1;
    size |= size >> 2;
    size |= size >> 4;
    size |= size >> 8;
    size |= size >> 16;
    return size + 1;
}

void initializeMemoryPool() {
    if (isInitialized) return;
    
    printf("Initializing memory pool...\n");
    
    // Initialize the entire pool as one large free block
    poolStart = (BlockHeader*)memoryPool;
    poolStart->size = POOL_SIZE - sizeof(BlockHeader);
    poolStart->isFree = 1;
    poolStart->next = NULL;
    poolStart->prev = NULL;
    poolStart->magic = MAGIC_FREE;
    
    isInitialized = 1;
    
    printf("Memory pool initialized: %d bytes available\n", POOL_SIZE);
    printf("Header size: %zu bytes\n", sizeof(BlockHeader));
    printf("Usable memory: %zu bytes\n", poolStart->size);
}

void* myMalloc(size_t size) {
    if (!isInitialized) initializeMemoryPool();
    
    if (size == 0) return NULL;
    
    // Align size to prevent fragmentation
    size = alignSize(size);
    
    BlockHeader* current = poolStart;
    
    // First-fit allocation strategy
    while (current) {
        if (current->isFree && current->size >= size) {
            // Check if we need to split the block
            if (current->size > size + sizeof(BlockHeader) + MIN_BLOCK_SIZE) {
                // Split the block
                BlockHeader* newBlock = (BlockHeader*)((char*)current + sizeof(BlockHeader) + size);
                newBlock->size = current->size - size - sizeof(BlockHeader);
                newBlock->isFree = 1;
                newBlock->next = current->next;
                newBlock->prev = current;
                newBlock->magic = MAGIC_FREE;
                
                if (current->next) {
                    current->next->prev = newBlock;
                }
                
                current->next = newBlock;
                current->size = size;
            }
            
            // Mark block as allocated
            current->isFree = 0;
            current->magic = MAGIC_ALLOCATED;
            
            // Update statistics
            totalAllocations++;
            totalBytesAllocated += size;
            
            return (char*)current + sizeof(BlockHeader);
        }
        current = current->next;
    }
    
    printf("ERROR: Out of memory! Requested: %zu bytes\n", size);
    return NULL; // No suitable block found
}

void myFree(void* ptr) {
    if (!ptr) return;
    
    BlockHeader* block = (BlockHeader*)((char*)ptr - sizeof(BlockHeader));
    
    // Validate block integrity
    if (block->magic != MAGIC_ALLOCATED) {
        printf("ERROR: Invalid magic number! Possible corruption or double-free.\n");
        return;
    }
    
    // Mark as free
    block->isFree = 1;
    block->magic = MAGIC_FREE;
    
    // Update statistics
    totalDeallocations++;
    totalBytesFreed += block->size;
    
    // Coalesce with next block if it's free
    if (block->next && block->next->isFree) {
        block->size += block->next->size + sizeof(BlockHeader);
        if (block->next->next) {
            block->next->next->prev = block;
        }
        block->next = block->next->next;
    }
    
    // Coalesce with previous block if it's free
    if (block->prev && block->prev->isFree) {
        block->prev->size += block->size + sizeof(BlockHeader);
        block->prev->next = block->next;
        if (block->next) {
            block->next->prev = block->prev;
        }
    }
}

void defragment() {
    printf("\n=== DEFRAGMENTATION PROCESS ===\n");
    
    BlockHeader* current = poolStart;
    int coalescedBlocks = 0;
    
    while (current && current->next) {
        if (current->isFree && current->next->isFree) {
            // Merge adjacent free blocks
            current->size += current->next->size + sizeof(BlockHeader);
            if (current->next->next) {
                current->next->next->prev = current;
            }
            current->next = current->next->next;
            coalescedBlocks++;
        } else {
            current = current->next;
        }
    }
    
    printf("Defragmentation complete: %d blocks coalesced\n", coalescedBlocks);
}

void printMemoryMap() {
    printf("\n=== MEMORY MAP ===\n");
    printf("Address    | Size  | Status    | Magic     | Next      | Prev\n");
    printf("-----------|-------|-----------|-----------|-----------|----------\n");
    
    BlockHeader* current = poolStart;
    int blockCount = 0;
    size_t totalFree = 0, totalAllocated = 0;
    
    while (current) {
        printf("%p | %5zu | %-9s | %08X | %p | %p\n",
               current,
               current->size,
               current->isFree ? "FREE" : "ALLOCATED",
               current->magic,
               current->next,
               current->prev);
        
        if (current->isFree) {
            totalFree += current->size;
        } else {
            totalAllocated += current->size;
        }
        
        blockCount++;
        current = current->next;
    }
    
    printf("\nMemory Summary:\n");
    printf("- Total blocks: %d\n", blockCount);
    printf("- Free memory: %zu bytes\n", totalFree);
    printf("- Allocated memory: %zu bytes\n", totalAllocated);
    printf("- Overhead (headers): %zu bytes\n", blockCount * sizeof(BlockHeader));
    printf("- Fragmentation: %.2f%%\n", calculateFragmentation());
}

double calculateFragmentation() {
    BlockHeader* current = poolStart;
    int freeBlocks = 0;
    size_t totalFree = 0;
    size_t largestFreeBlock = 0;
    
    while (current) {
        if (current->isFree) {
            freeBlocks++;
            totalFree += current->size;
            if (current->size > largestFreeBlock) {
                largestFreeBlock = current->size;
            }
        }
        current = current->next;
    }
    
    if (totalFree == 0) return 0.0;
    
    // Fragmentation = (1 - largest_free_block / total_free) * 100
    return (1.0 - (double)largestFreeBlock / totalFree) * 100.0;
}

int detectMemoryLeaks() {
    printf("\n=== MEMORY LEAK DETECTION ===\n");
    
    BlockHeader* current = poolStart;
    int leakedBlocks = 0;
    size_t leakedBytes = 0;
    
    printf("Allocated blocks still in memory:\n");
    printf("Address    | Size  | Status\n");
    printf("-----------|-------|-----------\n");
    
    while (current) {
        if (!current->isFree) {
            printf("%p | %5zu | LEAKED\n", current, current->size);
            leakedBlocks++;
            leakedBytes += current->size;
        }
        current = current->next;
    }
    
    if (leakedBlocks == 0) {
        printf("✅ No memory leaks detected!\n");
    } else {
        printf("❌ Memory leaks detected:\n");
        printf("- Leaked blocks: %d\n", leakedBlocks);
        printf("- Leaked bytes: %zu\n", leakedBytes);
    }
    
    return leakedBlocks;
}

void buddySystemAlloc() {
    printf("\n=== BUDDY SYSTEM ALLOCATION ===\n");
    
    size_t testSizes[] = {16, 32, 64, 128, 256};
    void* buddyPtrs[5];
    
    printf("Testing buddy system with power-of-2 sizes:\n");
    
    for (int i = 0; i < 5; i++) {
        size_t requestedSize = testSizes[i];
        size_t buddySize = isPowerOfTwo(requestedSize) ? requestedSize : nextPowerOfTwo(requestedSize);
        
        buddyPtrs[i] = myMalloc(buddySize);
        
        printf("Requested: %zu bytes, Allocated: %zu bytes, Pointer: %p\n",
               requestedSize, buddySize, buddyPtrs[i]);
    }
    
    printf("\nFreeing buddy allocations...\n");
    for (int i = 0; i < 5; i++) {
        myFree(buddyPtrs[i]);
        printf("Freed allocation %d\n", i + 1);
    }
}

void garbageCollection() {
    printf("\n=== GARBAGE COLLECTION ===\n");
    
    double fragmentation = calculateFragmentation();
    printf("Current fragmentation: %.2f%%\n", fragmentation);
    
    if (fragmentation > 30.0) {
        printf("Fragmentation exceeds 30%% - triggering garbage collection...\n");
        defragment();
        
        double newFragmentation = calculateFragmentation();
        printf("Fragmentation after GC: %.2f%%\n", newFragmentation);
        
        if (newFragmentation < fragmentation) {
            printf("✅ Garbage collection successful!\n");
        } else {
            printf("⚠️  Garbage collection had minimal effect.\n");
        }
    } else {
        printf("Fragmentation is acceptable - no GC needed.\n");
    }
}

void performStressTest() {
    printf("\n=== STRESS TEST ===\n");
    
    void* ptrs[100];
    int allocCount = 0;
    
    printf("Performing allocation stress test...\n");
    
    // Allocate various sizes
    for (int i = 0; i < 50; i++) {
        size_t size = (i % 10 + 1) * 32; // Sizes from 32 to 320 bytes
        ptrs[allocCount] = myMalloc(size);
        if (ptrs[allocCount]) {
            allocCount++;
        }
    }
    
    printf("Successfully allocated %d blocks\n", allocCount);
    
    // Free every other block to create fragmentation
    printf("Creating fragmentation by freeing every other block...\n");
    for (int i = 1; i < allocCount; i += 2) {
        myFree(ptrs[i]);
        ptrs[i] = NULL;
    }
    
    printf("Fragmentation after partial free: %.2f%%\n", calculateFragmentation());
    
    // Try to allocate large block
    printf("Attempting large allocation...\n");
    void* largePtr = myMalloc(1000);
    if (largePtr) {
        printf("✅ Large allocation successful\n");
        myFree(largePtr);
    } else {
        printf("❌ Large allocation failed due to fragmentation\n");
    }
    
    // Clean up remaining allocations
    printf("Cleaning up remaining allocations...\n");
    for (int i = 0; i < allocCount; i += 2) {
        if (ptrs[i]) {
            myFree(ptrs[i]);
        }
    }
}

void displayStatistics() {
    printf("\n=== MEMORY POOL STATISTICS ===\n");
    
    printf("Allocation Statistics:\n");
    printf("- Total allocations: %d\n", totalAllocations);
    printf("- Total deallocations: %d\n", totalDeallocations);
    printf("- Active allocations: %d\n", totalAllocations - totalDeallocations);
    printf("- Total bytes allocated: %zu\n", totalBytesAllocated);
    printf("- Total bytes freed: %zu\n", totalBytesFreed);
    printf("- Net allocated bytes: %zu\n", totalBytesAllocated - totalBytesFreed);
    
    // Calculate efficiency
    double efficiency = (double)(POOL_SIZE - sizeof(BlockHeader)) / POOL_SIZE * 100.0;
    printf("\nPool Efficiency:\n");
    printf("- Pool size: %d bytes\n", POOL_SIZE);
    printf("- Header overhead: %zu bytes\n", sizeof(BlockHeader));
    printf("- Efficiency: %.2f%%\n", efficiency);
    
    // Memory utilization
    BlockHeader* current = poolStart;
    size_t totalFree = 0, totalAllocated = 0;
    int freeBlocks = 0, allocatedBlocks = 0;
    
    while (current) {
        if (current->isFree) {
            totalFree += current->size;
            freeBlocks++;
        } else {
            totalAllocated += current->size;
            allocatedBlocks++;
        }
        current = current->next;
    }
    
    printf("\nCurrent State:\n");
    printf("- Free blocks: %d (%zu bytes)\n", freeBlocks, totalFree);
    printf("- Allocated blocks: %d (%zu bytes)\n", allocatedBlocks, totalAllocated);
    printf("- Utilization: %.2f%%\n", (double)totalAllocated / (totalAllocated + totalFree) * 100.0);
}

int main() {
    printf("Advanced Memory Pool Manager\n");
    printf("============================\n");
    
    // Initialize the memory pool
    initializeMemoryPool();
    
    // Test basic allocation and deallocation
    printf("\n=== BASIC ALLOCATION TEST ===\n");
    void* ptr1 = myMalloc(100);
    void* ptr2 = myMalloc(200);
    void* ptr3 = myMalloc(150);
    
    printf("Allocated 3 blocks:\n");
    printf("- ptr1 (100 bytes): %p\n", ptr1);
    printf("- ptr2 (200 bytes): %p\n", ptr2);
    printf("- ptr3 (150 bytes): %p\n", ptr3);
    
    printMemoryMap();
    
    // Test deallocation and coalescing
    printf("\n=== DEALLOCATION TEST ===\n");
    myFree(ptr2); // Free middle block
    printf("Freed middle block (ptr2)\n");
    printMemoryMap();
    
    myFree(ptr1); // Free first block
    myFree(ptr3); // Free last block
    printf("Freed remaining blocks\n");
    printMemoryMap();
    
    // Test buddy system
    buddySystemAlloc();
    
    // Test defragmentation
    defragment();
    printMemoryMap();
    
    // Perform stress test
    performStressTest();
    
    // Test garbage collection
    garbageCollection();
    
    // Detect memory leaks
    detectMemoryLeaks();
    
    // Display final statistics
    displayStatistics();
    
    printf("\n============================\n");
    printf("Memory pool manager test completed!\n");
    printf("============================\n");
    
    return 0;
}
