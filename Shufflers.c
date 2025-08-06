#include <math.h>
#include <string.h>
#include <stdint.h>

#include "Shufflers.h"

// ---------------------------- Functions -------------------------------- \\

void goldenShuffler(uint8_t *hashBox, const size_t capacity, const int rounds) {
    const double golden = 1.618033988;
    uint8_t tempBox[capacity];
    int roundsG = rounds * round(golden);
    memcpy(tempBox, hashBox, capacity);

    for (int i = 0; i < roundsG; i++) {
        double gM = golden * (i*i);
        int gM_R = round(gM);
        uint8_t Temp1 = tempBox[gM_R % capacity];
        tempBox[(i*2) % capacity] = Temp1;
    }

    memcpy(hashBox, tempBox, capacity);
}

void eulerShuffler(uint8_t *hashBox, const size_t capacity, const int rounds) {
    const double euler = 2.71828;
    uint8_t tempBox[capacity];
    int roundsE = rounds * (round(euler*5.77));
    memcpy(tempBox, hashBox, capacity);

    for (int i = 0; i < roundsE; i++) {
        double eM = euler * (i*i);
        int eMR = round(eM);
        uint8_t Temp1 = tempBox[eMR % capacity];
        tempBox[(i*2) % capacity] = Temp1;
    }

    memcpy(hashBox, tempBox, capacity);
}