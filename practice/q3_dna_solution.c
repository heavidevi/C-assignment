/*
===============================================================================
QUESTION 3 SOLUTION: DNA Sequence Analysis Engine
Programming Fundamentals - Mid Term Exam III
===============================================================================
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_SEQUENCE_LENGTH 10000
#define MAX_PATTERN_LENGTH 100

// Function prototypes
void computeLPS(char* pattern, int M, int* lps);
int KMPSearch(char* text, char* pattern, int positions[]);
void generateComplement(char* sequence, char* complement);
void reverseString(char* str);
int findOpenReadingFrames(char* sequence);
double calculateSequenceSimilarity(char* seq1, char* seq2);
void detectMutations(char* seq1, char* seq2);
int isPalindromic(char* sequence);
double calculateGCContent(char* sequence);

// KMP Algorithm implementation for efficient pattern matching
void computeLPS(char* pattern, int M, int* lps) {
    int len = 0;  // length of the previous longest prefix suffix
    lps[0] = 0;   // lps[0] is always 0
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

int KMPSearch(char* text, char* pattern, int positions[]) {
    int M = strlen(pattern);
    int N = strlen(text);
    int count = 0;
    
    // Create lps array
    int* lps = (int*)malloc(sizeof(int) * M);
    computeLPS(pattern, M, lps);
    
    int i = 0; // index for text
    int j = 0; // index for pattern
    
    while (i < N) {
        if (pattern[j] == text[i]) {
            j++;
            i++;
        }
        
        if (j == M) {
            positions[count] = i - j;
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
        switch (toupper(sequence[i])) {
            case 'A': complement[i] = 'T'; break;
            case 'T': complement[i] = 'A'; break;
            case 'G': complement[i] = 'C'; break;
            case 'C': complement[i] = 'G'; break;
            default: complement[i] = 'N'; break; // Unknown nucleotide
        }
    }
    complement[len] = '\0';
    
    // Reverse the complement to get the complementary strand
    reverseString(complement);
}

void reverseString(char* str) {
    int len = strlen(str);
    for (int i = 0; i < len / 2; i++) {
        char temp = str[i];
        str[i] = str[len - 1 - i];
        str[len - 1 - i] = temp;
    }
}

int findOpenReadingFrames(char* sequence) {
    int len = strlen(sequence);
    int orfCount = 0;
    
    printf("   Open Reading Frames Analysis:\n");
    printf("   Frame | Start | Stop  | Length | Sequence Preview\n");
    printf("   ------|-------|-------|--------|-----------------\n");
    
    // Check all 3 reading frames
    for (int frame = 0; frame < 3; frame++) {
        for (int i = frame; i < len - 5; i += 3) {
            // Look for start codon "ATG"
            if (strncmp(&sequence[i], "ATG", 3) == 0) {
                // Found start codon, look for stop codons
                for (int j = i + 3; j < len - 2; j += 3) {
                    if (strncmp(&sequence[j], "TAA", 3) == 0 || 
                        strncmp(&sequence[j], "TAG", 3) == 0 || 
                        strncmp(&sequence[j], "TGA", 3) == 0) {
                        
                        int orfLength = j + 3 - i;
                        char preview[21];
                        strncpy(preview, &sequence[i], 20);
                        preview[20] = '\0';
                        
                        printf("     %d   | %5d | %5d | %6d | %s...\n", 
                               frame + 1, i, j + 2, orfLength, preview);
                        
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

double calculateSequenceSimilarity(char* seq1, char* seq2) {
    int len1 = strlen(seq1);
    int len2 = strlen(seq2);
    int minLen = (len1 < len2) ? len1 : len2;
    int maxLen = (len1 > len2) ? len1 : len2;
    int matches = 0;
    
    // Count exact matches
    for (int i = 0; i < minLen; i++) {
        if (toupper(seq1[i]) == toupper(seq2[i])) {
            matches++;
        }
    }
    
    // Calculate similarity as percentage of the longer sequence
    return (double)matches / maxLen * 100.0;
}

void detectMutations(char* seq1, char* seq2) {
    int len1 = strlen(seq1);
    int len2 = strlen(seq2);
    int minLen = (len1 < len2) ? len1 : len2;
    
    int substitutions = 0;
    int insertions = 0;
    int deletions = 0;
    
    printf("\n   Mutation Analysis:\n");
    printf("   Position | Seq1 | Seq2 | Type\n");
    printf("   ---------|------|------|------------\n");
    
    for (int i = 0; i < minLen; i++) {
        if (toupper(seq1[i]) != toupper(seq2[i])) {
            printf("   %8d | %4c | %4c | Substitution\n", 
                   i, seq1[i], seq2[i]);
            substitutions++;
        }
    }
    
    // Detect insertions/deletions based on length difference
    if (len1 > len2) {
        deletions = len1 - len2;
        printf("   %8s | %4s | %4s | %d Deletions\n", "End", "-", "N/A", deletions);
    } else if (len2 > len1) {
        insertions = len2 - len1;
        printf("   %8s | %4s | %4s | %d Insertions\n", "End", "N/A", "-", insertions);
    }
    
    printf("\n   Mutation Summary:\n");
    printf("   - Substitutions: %d\n", substitutions);
    printf("   - Insertions: %d\n", insertions);
    printf("   - Deletions: %d\n", deletions);
    printf("   - Total mutations: %d\n", substitutions + insertions + deletions);
}

int isPalindromic(char* sequence) {
    char complement[MAX_SEQUENCE_LENGTH];
    generateComplement(sequence, complement);
    return strcmp(sequence, complement) == 0;
}

double calculateGCContent(char* sequence) {
    int len = strlen(sequence);
    int gcCount = 0;
    
    for (int i = 0; i < len; i++) {
        char base = toupper(sequence[i]);
        if (base == 'G' || base == 'C') {
            gcCount++;
        }
    }
    
    return (double)gcCount / len * 100.0;
}

void performPatternMatching() {
    printf("\n=== PATTERN MATCHING ANALYSIS ===\n");
    
    char dnaSequence[] = "ATGCGATCGATGAAATCGATGCCCTAGATGTTATAATCGATGCCCATGAAATAG";
    char patterns[][20] = {"ATG", "ATCG", "TAG", "GCC", "AAT"};
    int numPatterns = 5;
    
    printf("DNA Sequence: %s\n", dnaSequence);
    printf("Length: %lu bases\n\n", strlen(dnaSequence));
    
    for (int p = 0; p < numPatterns; p++) {
        int positions[100];
        int matchCount = KMPSearch(dnaSequence, patterns[p], positions);
        
        printf("Pattern '%s':\n", patterns[p]);
        printf("- Matches found: %d\n", matchCount);
        
        if (matchCount > 0) {
            printf("- Positions: ");
            for (int i = 0; i < matchCount; i++) {
                printf("%d ", positions[i]);
            }
            printf("\n");
        }
        printf("\n");
    }
}

void performComplementAnalysis() {
    printf("=== COMPLEMENTARY STRAND ANALYSIS ===\n");
    
    char sequence[] = "ATGCGATCGATGAAATCGATGCC";
    char complement[MAX_SEQUENCE_LENGTH];
    
    generateComplement(sequence, complement);
    
    printf("Original sequence:     %s\n", sequence);
    printf("Complementary strand:  %s\n", complement);
    
    // Check if palindromic
    if (isPalindromic(sequence)) {
        printf("Status: This sequence is palindromic!\n");
    } else {
        printf("Status: This sequence is not palindromic.\n");
    }
    
    // Calculate GC content for both strands
    double originalGC = calculateGCContent(sequence);
    double complementGC = calculateGCContent(complement);
    
    printf("GC Content - Original: %.2f%%, Complement: %.2f%%\n", 
           originalGC, complementGC);
    
    printf("\n");
}

void performReadingFrameAnalysis() {
    printf("=== READING FRAME ANALYSIS ===\n");
    
    char sequence[] = "ATGCGATCGATGAAATCGATGCCCTAGATGTTATAATCGATGCCCATGAAATAGTAG";
    
    printf("Analyzing sequence: %s\n", sequence);
    printf("Length: %lu bases\n\n", strlen(sequence));
    
    int orfCount = findOpenReadingFrames(sequence);
    
    printf("\n   Total ORFs found: %d\n", orfCount);
    
    if (orfCount > 0) {
        printf("   Analysis: Sequence contains potential protein-coding regions.\n");
    } else {
        printf("   Analysis: No complete ORFs found in this sequence.\n");
    }
    
    printf("\n");
}

void performSimilarityAnalysis() {
    printf("=== SEQUENCE SIMILARITY ANALYSIS ===\n");
    
    char sequence1[] = "ATGCGATCGATGAAATCGATGCCC";
    char sequence2[] = "ATGCGATCGATGAAATCGATGAAA";
    char sequence3[] = "GGCATCGATCGATGAAATCGATCC";
    
    printf("Sequence 1: %s\n", sequence1);
    printf("Sequence 2: %s\n", sequence2);
    printf("Sequence 3: %s\n\n", sequence3);
    
    // Compare sequences
    double sim12 = calculateSequenceSimilarity(sequence1, sequence2);
    double sim13 = calculateSequenceSimilarity(sequence1, sequence3);
    double sim23 = calculateSequenceSimilarity(sequence2, sequence3);
    
    printf("Similarity Analysis:\n");
    printf("- Sequence 1 vs 2: %.2f%% similar\n", sim12);
    printf("- Sequence 1 vs 3: %.2f%% similar\n", sim13);
    printf("- Sequence 2 vs 3: %.2f%% similar\n", sim23);
    
    // Determine closest sequences
    if (sim12 > sim13 && sim12 > sim23) {
        printf("- Closest pair: Sequences 1 and 2\n");
    } else if (sim13 > sim12 && sim13 > sim23) {
        printf("- Closest pair: Sequences 1 and 3\n");
    } else {
        printf("- Closest pair: Sequences 2 and 3\n");
    }
    
    printf("\n");
}

void performMutationDetection() {
    printf("=== MUTATION DETECTION ANALYSIS ===\n");
    
    char wildType[] = "ATGCGATCGATGAAATCGATGCCC";
    char mutated[]  = "ATGCGATCGATGACATCGATGCCC";
    
    printf("Wild-type sequence: %s\n", wildType);
    printf("Mutated sequence:   %s\n", mutated);
    
    detectMutations(wildType, mutated);
    
    printf("\n");
}

void generateSequenceStatistics() {
    printf("=== SEQUENCE STATISTICS ===\n");
    
    char sequence[] = "ATGCGATCGATGAAATCGATGCCCTAGATGTTATAATCGATGCCC";
    int len = strlen(sequence);
    
    // Count nucleotides
    int counts[4] = {0}; // A, T, G, C
    for (int i = 0; i < len; i++) {
        switch (toupper(sequence[i])) {
            case 'A': counts[0]++; break;
            case 'T': counts[1]++; break;
            case 'G': counts[2]++; break;
            case 'C': counts[3]++; break;
        }
    }
    
    printf("Sequence: %s\n", sequence);
    printf("Length: %d bases\n\n", len);
    
    printf("Nucleotide Composition:\n");
    printf("- Adenine (A):  %d bases (%.2f%%)\n", counts[0], (counts[0] * 100.0) / len);
    printf("- Thymine (T):  %d bases (%.2f%%)\n", counts[1], (counts[1] * 100.0) / len);
    printf("- Guanine (G):  %d bases (%.2f%%)\n", counts[2], (counts[2] * 100.0) / len);
    printf("- Cytosine (C): %d bases (%.2f%%)\n", counts[3], (counts[3] * 100.0) / len);
    
    double gcContent = calculateGCContent(sequence);
    printf("\nGC Content: %.2f%%\n", gcContent);
    
    // Sequence classification based on GC content
    if (gcContent < 30) {
        printf("Classification: AT-rich sequence\n");
    } else if (gcContent > 70) {
        printf("Classification: GC-rich sequence\n");
    } else {
        printf("Classification: Balanced composition\n");
    }
    
    printf("\n");
}

int main() {
    printf("DNA Sequence Analysis Engine\n");
    printf("============================\n");
    
    // Perform all analyses
    performPatternMatching();
    performComplementAnalysis();
    performReadingFrameAnalysis();
    performSimilarityAnalysis();
    performMutationDetection();
    generateSequenceStatistics();
    
    printf("============================\n");
    printf("DNA analysis completed successfully!\n");
    printf("============================\n");
    
    return 0;
}
