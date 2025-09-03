#include <stdint.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

// ------------------------------- Intern Libraries --------------------------------- \\

#include "../include/Shufflers.h"
#include "../include/Solutioners.h"
#include "../include/Logics.h"
#include "../include/Salting.h"

// -------------------------------- function ----------------------------------- \\

char* hash (const char input[], uint16_t rounds, uint16_t salting)  {
    const size_t limit = 128;
    uint8_t hashBox[limit];
    uint16_t g_rounds = 0;
    memset(hashBox, 0, limit);

    const size_t sizeInput = strlen(input);
    uint8_t inputHex[sizeInput];
    converter(input, sizeInput, inputHex);

    if (salting < 0) {
        saltAdd(inputHex, sizeInput, salting);
    }
    else {
        salting = 0;
    }

    if (rounds == 0 || rounds == 1) {
        g_rounds = 64;
    }
    else {
        g_rounds = rounds;
    }

    uint32_t sumHash = 0;
    for (size_t i = 0; i < sizeInput; i++) {
        sumHash += inputHex[i];
    }
    uint32_t oeInput = sumHash % 2;

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

    for (int i = 0; i < round(g_rounds/2); i++) {
        goldenShuffler(hashBox, limit, g_rounds);
        logicOpps(hashBox, oeInput , limit);
        logMathOpps(hashBox, oeInput , limit);
        eulerShuffler(hashBox, limit, g_rounds);
    }

    differentiator(hashBox, limit);
    weakIndexCorrector(hashBox, limit, inputHex, sizeInput);

    char* hashStr = malloc(limit * 2 + 1);
    if (!hashStr) return NULL;

    static const char hex_digits[] = "0123456789abcdef";
    for (size_t i = 0; i < limit; i++) {
        hashStr[i * 2]     = hex_digits[hashBox[i] >> 4];
        hashStr[i * 2 + 1] = hex_digits[hashBox[i] & 0x0F];
    }
    hashStr[limit * 2] = '\0';

    return hashStr; // caller must free()
}