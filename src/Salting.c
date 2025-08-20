#include <stdint.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>

#include "../include/Salting.h"

void saltAdd(uint8_t *hashBox, size_t originalSize, size_t salting_Rounds) {
    const double feigenbaum = 4.669201;
    const uint8_t saltList[] = {
        0x21, 0x3A, 0x73, 0x7A,
        0x45, 0x50, 0x61, 0x4D,
        0x77, 0x4C, 0x69, 0x67,
        0x4C, 0x2E, 0x5C, 0x6A
    };
    const size_t saltSize = sizeof(saltList) / sizeof(saltList[0]);

    // Make sure we have enough space in the destination
    uint8_t *tempbox = malloc(originalSize + salting_Rounds);
    if (!tempbox) return; // malloc failed
    memcpy(tempbox, hashBox, originalSize);

    for (size_t i = 0; i < salting_Rounds; i++) {
        // use a valid base from the original data
        uint8_t base = hashBox[i % originalSize];

        // avoid division by zero
        double fB = (i == 0) ? (base * feigenbaum) : (base * feigenbaum) / (double)i;

        int fBR = (int)fabs(round(fB)) % saltSize; // keep index inside saltList
        tempbox[originalSize + i] = saltList[fBR];
    }

    // Copy back to the original buffer (caller must have allocated enough space!)
    memcpy(hashBox, tempbox, originalSize + salting_Rounds);

    free(tempbox);
}