#include <stdio.h>
#include <stdint.h>
#include <string.h>

// ------------------------------- Intern Libraries --------------------------------- \\

#include "Shufflers.h"
#include "Solutioners.h"
#include "Logics.h"

// ----------------------------------- Structs -------------------------------------- \\

struct hash1024 {
    uint8_t hexBox[128];
    uint16_t id;
};

// ------------------------------ Function Prototypes -------------------------------- \\



// -------------------------------- Main ----------------------------------- \\

int main() {
    // consts:
    const size_t limit = 128;
    const int buffer = 512;
    const int generalRounds = 64;

    // Main variables:
    char input[buffer];
    uint8_t inputHex[buffer];
    uint8_t hashBox[limit];

    memset(hashBox, 0, limit);

    // Getters:
    printf("Enter input: ");
    fgets(input, buffer, stdin);
    input[strlen(input) - 1] = '\0';

    // size of the input:
    size_t sizeInput = strlen(input);
    printf("Input size: %zu\n", sizeInput);

    // Converting and printing:
    converter(input, sizeInput, inputHex);
    printf("Hexs:");
    for (int i = 0; i < sizeInput; i++) {
        printf("0x%02X ", inputHex[i]);
        if ((i + 1) % 16 == 0) printf("\n");
    }

    // fill or compact (please, do not change here):
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

    // Just use one of the shuffling methods!
    goldenShuffler(hashBox, limit, generalRounds);
    differentiator(hashBox, limit);

    // corrector:
    corrector(hashBox, limit, inputHex, sizeInput);

    // Printing Hash:
    printf("\n\n\n Hex output:\n");
    for (int i = 0; i < limit; i++) {
        printf("0x%02X ", hashBox[i]);
        if ((i + 1) % 16 == 0) printf("\n");
    }

    return 0;
}

// ---------------------------- Functions -------------------------------- \\