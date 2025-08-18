#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <sys/resource.h>
#include <time.h>

// ------------------------------- Intern Libraries --------------------------------- \\

#include "Internal_dependencies/Shufflers.h"
#include "Internal_dependencies/Solutioners.h"
#include "Internal_dependencies/Logics.h"
#include "Internal_dependencies/Salting.h"

// -------------------------------- Main ----------------------------------- \\

void print_memory_usage() {
    struct rusage usage;
    getrusage(RUSAGE_SELF, &usage);
    printf("Memory used: %ld kilobytes\n", usage.ru_maxrss);
}

int main() {

    clock_t start, end;
    double cpu_time_used;

    // consts:
    const size_t limit = 128;
    const int buffer = 1048576;
    const int generalRounds = 64;
    const size_t salting_rounds = 16;
    char input[buffer];
    uint8_t inputHex[buffer];
    uint8_t hashBox[limit];

    print_memory_usage();

    memset(hashBox, 0, limit);

    // Getters:
    printf("Enter input: ");
    fgets(input, buffer, stdin);
    size_t sizeInput = strcspn(input, "\n");
    input[sizeInput] = '\0';

    start = clock();

    printf("Input size: %zu\n", sizeInput);

    converter(input, sizeInput, inputHex);
    saltAdd(inputHex, sizeInput, salting_rounds);
    printf("Hexs:");
    for (int i = 0; i < sizeInput; i++) {
        printf("0x%02X ", inputHex[i]);
        if ((i + 1) % 16 == 0) printf("\n");
    }

    uint32_t sumHash = 0;
    for (size_t i = 0; i < sizeInput; i++) {
        sumHash += inputHex[i];
    }
    uint32_t oeInput = sumHash % 2;

    // Using Internal dependencies:
    if (sizeInput < limit) {
        autoFill(inputHex, sizeInput, limit, hashBox);
    }
    else if (sizeInput == limit) {
        for (int i = 0; i < sizeInput; i++) {
            hashBox[i] = inputHex[i];
        }
    }
    else {
        compactor(inputHex, sizeInput, limit, hashBox);
    }

    differentiator(hashBox, limit);

    for (int i = 0; i < generalRounds/2; i++) {
        goldenShuffler(hashBox, limit, generalRounds);
        logicOpps(hashBox, oeInput , limit);
        logMathOpps(hashBox, oeInput , limit);
        eulerShuffler(hashBox, limit, generalRounds);
    }

    differentiator(hashBox, limit);
    weakIndexCorrector(hashBox, limit, inputHex, sizeInput);

    // array of hash to string of hash

    char hashStr[limit * 2 + 1];
    static const char hex_digits[] = "0123456789abcdef";

    for (size_t i = 0; i < limit; i++) {
        hashStr[i * 2]     = hex_digits[hashBox[i] >> 4];
        hashStr[i * 2 + 1] = hex_digits[hashBox[i] & 0x0F];
    }
    hashStr[limit * 2] = '\0';

    // Printing Hash:
    printf("\n\n\n Hex output: 0x%s \n\n", hashStr);

    end = clock();

    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    printf("Execution time: %.6f seconds\n", cpu_time_used);

    print_memory_usage();

    return 0;
}