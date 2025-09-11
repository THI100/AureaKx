#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <time.h>

#include "../include/AureaKx.h"

// --- Config ---
#define NUM_TESTS 200000   // Change between 1000 and 1000000
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

int main(void) {
    srand((unsigned)time(NULL));

    char **hashes = malloc(NUM_TESTS * sizeof(char*));
    char **inputs = malloc(NUM_TESTS * sizeof(char*)); // keep original inputs too
    if (!hashes || !inputs) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }

    size_t collisions = 0;

    for (size_t i = 0; i < NUM_TESTS; i++) {
        char input[MAX_INPUT_LEN];
        unique_utf8_string(input, MAX_INPUT_LEN, i + 1); // Always unique

        // Run your hash function
        char *h = hash(input, 100, 42); // Example rounds & salting
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

    printf("\nTotal tests: %d\n", NUM_TESTS);
    printf("Collisions found: %zu\n", collisions);

    // Cleanup
    for (size_t i = 0; i < NUM_TESTS; i++) {
        free(hashes[i]);
        free(inputs[i]);
    }
    free(hashes);
    free(inputs);

    return 0;
}
