#include <stdint.h>
#include <math.h>
#include <string.h>

#include "Salting.h"

void saltAdd (uint8_t *hashBox, const size_t originalSize) {
    const int saltAmount = 16;
    const double feigenbaum = 4.669201;
    uint8_t tempbox[originalSize + saltAmount];
    memcpy(tempbox, hashBox, originalSize + saltAmount);

    const uint8_t saltList[] = {0x21, 0x3A, 0x73, 0x7A, 0x45, 0x50, 0x61, 0x4D,
                                0x77, 0x4C, 0x69, 0x67, 0x4C, 0x2E, 0x5C, 0x6A};

    for (int i = 0; i < saltAmount; i++) {
        uint8_t base = tempbox[originalSize];
        double fB = (base*feigenbaum)/i;
        int fBR = round(fB);
        tempbox[originalSize + i] = saltList[fBR];
    }

    memcpy(hashBox, tempbox, originalSize + saltAmount);
}
