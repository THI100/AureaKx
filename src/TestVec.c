#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <time.h>
#include <sys/resource.h>
#include <stddef.h>

#include "../include/AureaKx.h"

// --- Config ---
#define NUM_TESTS_PI 10000000
#define NUM_TESTS_COL 2000000
#define MAX_INPUT_LEN 128
#define HASH_LEN 128   // <-- adjust to your actual hash length

void unique_utf8_string(char *buf, size_t max_len, unsigned long long counter) {
    static unsigned long long seed = 0;
    if (seed == 0) {
        unsigned long long t = (unsigned long long)time(NULL);
        uintptr_t addr = (uintptr_t)&seed;
        seed = t ^ (addr * 0x9E3779B97F4A7C15ULL);
        seed ^= (seed >> 30);
        seed *= 0xBF58476D1CE4E5B9ULL;
        seed ^= (seed >> 27);
        seed *= 0x94D049BB133111EBULL;
        seed ^= (seed >> 31);
    }

    unsigned long long x = counter ^ (seed + (counter << 17) | (counter >> 13));
    x = (x ^ (x >> 30)) * 0xBF58476D1CE4E5B9ULL;
    x = (x ^ (x >> 27)) * 0x94D049BB133111EBULL;
    x ^= (x >> 31);

    size_t i = 0;
    while (x > 0 && i < max_len - 1) {
        buf[i++] = (char)(32 + (x % 95));
        x /= 95;
    }
    buf[i] = '\0';
}

void print_memory_usage() {
    struct rusage usage;
    getrusage(RUSAGE_SELF, &usage);
    printf("Memory used: %ld kilobytes\n", usage.ru_maxrss);
}

// --- Simple hash table for collision detection ---
typedef struct {
    uint64_t hash_code;
    char hash_str[HASH_LEN + 1];
    char input[MAX_INPUT_LEN];
    int used;
} HashEntry;

#define TABLE_SIZE (NUM_TESTS_COL * 2 + 1)

static inline uint64_t fast64(const char *s) {
    uint64_t h = 1469598103934665603ULL;
    for (; *s; ++s)
        h = (h ^ (unsigned char)*s) * 1099511628211ULL;
    return h;
}

int main(void) {
    clock_t start, end;
    double cpu_time_used;
    int nc = 0;

    printf("Select option: 1 = collision, 2 = pre-image.\n");
    scanf("%d", &nc);

    if (nc == 1) {
        start = clock();

        size_t collisions = 0;
        HashEntry *table = calloc(TABLE_SIZE, sizeof(HashEntry));
        if (!table) {
            fprintf(stderr, "Memory allocation failed\n");
            return 1;
        }

        for (size_t i = 0; i < NUM_TESTS_COL; i++) {
            char input[MAX_INPUT_LEN];
            unique_utf8_string(input, MAX_INPUT_LEN, i + 1);
            char *h = hash(input, 42);
            if (!h) continue;

            uint64_t hc = fast64(h);
            size_t pos = hc % TABLE_SIZE;

            // Linear probing
            while (table[pos].used) {
                if (memcmp(table[pos].hash_str, h, HASH_LEN) == 0) {
                    collisions++;
                    printf("\n[COLLISION #%zu]\nInput A: %s\nInput B: %s\nHash   : %s\n",
                           collisions, table[pos].input, input, h);
                    break;
                }
                pos = (pos + 1) % TABLE_SIZE;
            }

            // Insert if empty
            if (!table[pos].used) {
                table[pos].used = 1;
                table[pos].hash_code = hc;
                strncpy(table[pos].hash_str, h, HASH_LEN);
                strncpy(table[pos].input, input, MAX_INPUT_LEN);
            }
        }

        printf("\nTotal tests: %d\nCollisions found: %zu\n", NUM_TESTS_COL, collisions);
        print_memory_usage();

        free(table);
        end = clock();
        cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
        printf("Execution time: %.6f seconds\n", cpu_time_used);
    }

    else if (nc == 2) {
        start = clock();
        const char *targetInput = "SecretMessage123";
        char *targetHash = hash(targetInput, 42);
        if (!targetHash) {
            fprintf(stderr, "Target hash failed.\n");
            return 1;
        }

        printf("Target Input: %s\nTarget Hash : %s\n", targetInput, targetHash);

        size_t found = 0;
        for (size_t i = 1; i <= NUM_TESTS_PI; i++) {
            char candidate[MAX_INPUT_LEN];
            unique_utf8_string(candidate, MAX_INPUT_LEN, i);
            char *h = hash(candidate, 42);
            if (!h) continue;

            if (memcmp(h, targetHash, HASH_LEN) == 0 && strcmp(candidate, targetInput) != 0) {
                printf("[PRE-IMAGE FOUND]\nCandidate: %s\nHash: %s\n", candidate, h);
                found = 1;
                break;
            }
        }

        print_memory_usage();
        if (!found)
            printf("No pre-image found after %d attempts.\n", NUM_TESTS_PI);

        end = clock();
        cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
        printf("Execution time: %.6f seconds\n", cpu_time_used);
    }

    else {
        printf("Invalid option.\n");
    }

    return 0;
}
