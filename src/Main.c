#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <sys/resource.h>
#include <time.h>

#include "../include/AureaKx.h"

void print_memory_usage() {
    struct rusage usage;
    getrusage(RUSAGE_SELF, &usage);
    printf("Memory used: %ld kilobytes\n", usage.ru_maxrss);
}

int main() {
    const char *input = "The quick brown fox jumps over the lazy dog";
    uint16_t salting = 45; // Example salting value

    clock_t start = clock();
    char *hash_result = hash(input, salting);
    clock_t end = clock();

    if (hash_result) {
        printf("Input: %s\n", input);
        printf("Hash: %s\n", hash_result);
        printf("Time taken: %.6f seconds\n", (double)(end - start) / CLOCKS_PER_SEC);
        print_memory_usage();
        free(hash_result);
    } else {
        printf("Hashing failed due to memory allocation error.\n");
    }

    return 0;
}