#include <stdio.h>
#include <stdint.h>
#include <string.h>

// ------------------------------- Intern Libraries --------------------------------- \\

#include "Internal_dependencies/Shufflers.h"
#include "Internal_dependencies/Solutioners.h"
#include "Internal_dependencies/Logics.h"
#include "Internal_dependencies/Salting.h"

// -------------------------------- Main ----------------------------------- \\

int main() {

    // consts:
    const size_t limit = 128;
    const int buffer = 512;
    const int generalRounds = 64;
    const size_t salting_rounds = 16;
    char input[buffer];
    uint8_t inputHex[buffer];
    uint8_t hashBox[limit];

    memset(hashBox, 0, limit);

    // Getters:
    printf("Enter input: ");
    fgets(input, buffer, stdin);
    input[strlen(input) - 1] = '\0';

    size_t sizeInput = strlen(input);
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
    for (size_t i = 0; i < limit; i++) {
        sprintf(hashStr + (i * 2), "%02x", hashBox[i]);
    }
    hashStr[limit * 2] = '\0';

    // Printing Hash:
    printf("\n\n\n Hex output: 0x%s", hashStr);

    return 0;
}