#include <string.h>
#include <stdint.h>

#include "Logics.h"


void logicOpps(uint8_t *hashBox, int oddevenInput, const size_t capacity) {
    uint8_t tempBox[capacity];
    memcpy(tempBox, hashBox, capacity);


    for (size_t i = 0; i < (capacity / 2); i++) {
        int Temp1 = tempBox[i];
        int Temp2 = tempBox[i * oddevenInput];

        switch (i) {
            case 0:
            case 1:
            case 2:
            case 3:
            case 4:
            case 5:
            case 6:
            case 7:
            case 8:
            case 9:
            case 10:
            case 11:
            case 12:
            // ...

            default: {
                return;
            }

        }
    }

    memcpy(hashBox, tempBox, capacity);
}

void logMathOpps(uint8_t *hashBox, int oddevenInput, const size_t capacity) {
    // Consts:
    const double golden = 1.618;
    const double euler = 2.7;
    const double Plack = ;
    const double avogrado = ;

    uint8_t tempBox[capacity];
    memcpy(tempBox, hashBox, capacity);


    for (size_t i = 0; i < ((capacity / 4) * 3); i++) {
        int Temp1 = tempBox[i];
        int Temp2 = tempBox[i * oddevenInput];

        switch (i) {
            case 0:
            case 1:

            default: {
                return;
            }

        }
    }

    memcpy(hashBox, tempBox, capacity);
}
