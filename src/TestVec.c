#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <time.h>
#include <sys/resource.h>

#include "../include/AureaKx.h"

// --- Config ---
#define NUM_TESTS_PI 10000000   // limit of C programming language, 10 millions of attempts
#define NUM_TESTS_COL 200000    // limit of performance, 200 Thousands of attempts
#define MAX_INPUT_LEN 128  // Max length of generated input strings

// Generate a unique deterministic string from an integer counter
void unique_utf8_string(char *buf, size_t max_len, unsigned long long counter) {
    // Convert counter to base-95 (printable ASCII range 32–126)
    size_t i = 0;
    while (counter > 0 && i < max_len - 1) {
        buf[i++] = (char)(32 + (counter % 95));
        counter /= 95;
    }
    buf[i] = '\0';
}

void print_memory_usage() {
    struct rusage usage;
    getrusage(RUSAGE_SELF, &usage);
    printf("Memory used: %ld kilobytes\n", usage.ru_maxrss);
}

int main(void) {

    clock_t start, end;
    double cpu_time_used;

    int nc = 0;
    printf("select a option of test, 1 for collision and 2 for second pre-image. \n");
    scanf("%d", &nc);

    if (nc == 1) {
        start = clock();

        srand((unsigned)time(NULL));

        char **hashes = malloc(NUM_TESTS_COL * sizeof(char*));
        char **inputs = malloc(NUM_TESTS_COL * sizeof(char*)); // keep original inputs too
        if (!hashes || !inputs) {
            fprintf(stderr, "Memory allocation failed\n");
            return 1;
        }

        size_t collisions = 0;

        for (size_t i = 0; i < NUM_TESTS_COL; i++) {
            char input[MAX_INPUT_LEN];
            unique_utf8_string(input, MAX_INPUT_LEN, i + 1); // Always unique

            // Run your hash function
            char *h = hash(input, 42); // Example rounds & salting
            if (!h) continue;

            // Save both the input and its hash
            inputs[i] = strdup(input);
            hashes[i] = strdup(h);

            // Compare with all previous hashes
            for (size_t j = 0; j < i; j++) {
                if (strcmp(hashes[i], hashes[j]) == 0) {
                    collisions++;
                    printf("\n[COLLISION #%zu]\n", collisions);
                    printf("  Input A: %s\n", inputs[j]);
                    printf("  Input B: %s\n", inputs[i]);
                    printf("  Hash   : %s\n", hashes[i]);
                    break;  // count once per new string
                }
            }
        }

        printf("\nTotal tests: %d\n", NUM_TESTS_COL);
        printf("Collisions found: %zu\n", collisions);

        print_memory_usage();

        // Cleanup
        for (size_t i = 0; i < NUM_TESTS_COL; i++) {
            free(hashes[i]);
            free(inputs[i]);
        }
        free(hashes);
        free(inputs);

        end = clock();

        cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
        printf("Execution time: %.6f seconds\n", cpu_time_used);
    }

    else if (nc == 2) {
        start = clock();

        srand((unsigned)time(NULL));

        // Pick a known target
        const char *targetInput = "SecretMessage123";
        char *targetHash = hash(targetInput, 42); // Example parameter
        if (!targetHash) {
            fprintf(stderr, "Target hash computation failed\n");
            return 1;
        }

        printf("Target Input: %s\n", targetInput);
        printf("Target Hash : %s\n\n", targetHash);

        // Attempt to find a pre-image
        size_t found = 0;
        for (size_t i = 1; i <= NUM_TESTS_PI; i++) {
            char candidate[MAX_INPUT_LEN];
            unique_utf8_string(candidate, MAX_INPUT_LEN, i);

            char *h = hash(candidate, 42);
            if (!h) continue;

            if (strcmp(h, targetHash) == 0 && strcmp(candidate, targetInput) != 0) {
                printf("[PRE-IMAGE FOUND]\n");
                printf("  Candidate Input: %s\n", candidate);
                printf("  Hash           : %s\n", h);
                found = 1;
                break;
            }
        }

        print_memory_usage();

        if (!found) {
            printf("No pre-image found after %d attempts.\n", NUM_TESTS_PI);
        }
        
        end = clock();

        cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
        printf("Execution time: %.6f seconds\n", cpu_time_used);
    }


    else {
        printf("Error: invalid input.");
    }

    return 0;
}