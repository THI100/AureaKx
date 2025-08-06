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
            case 0: tempBox[i] = Temp1 ^ Temp2; break;                        // XOR
            case 1: tempBox[i] = Temp1 & Temp2; break;                        // AND
            case 2: tempBox[i] = ~(Temp1 & Temp2); break;                     // NAND
            case 3: tempBox[i] = ~(Temp1 | Temp2); break;                     // NOR
            case 4: tempBox[i] = Temp1 | Temp2; break;                        // OR
            case 5: tempBox[i] = (Temp1 ^ Temp2) & 0xFF; break;               // XOR masked
            case 6: tempBox[i] = (Temp1 & ~Temp2); break;                     // A AND NOT B
            case 7: tempBox[i] = (Temp2 & ~Temp1); break;                     // B AND NOT A
            case 8: tempBox[i] = ((Temp1 << 1) | (Temp1 >> 7)) & 0xFF; break; // Rotate left
            case 9: tempBox[i] = ((Temp2 >> 1) | (Temp2 << 7)) & 0xFF; break; // Rotate right
            case 10: tempBox[i] = ~(Temp1 ^ Temp2); break;                    // XNOR
            case 11: tempBox[i] = (Temp1 + Temp2) & 0xFF; break;              // Add mod 256
            case 12: tempBox[i] = (Temp1 - Temp2) & 0xFF; break;              // Sub mod 256
            case 13: tempBox[i] = (Temp1 | Temp2) ^ (Temp1 & Temp2); break;   // XOR via OR-AND
            case 14: tempBox[i] = (Temp1 >> 2) | (Temp2 << 6); break;         // Bit blend
            case 15: tempBox[i] = (Temp1 ^ (Temp2 << 1)) & 0xFF; break;       // XOR with shift
            default: return;
        }
    }

    memcpy(hashBox, tempBox, capacity);
}


void logMathOpps(uint8_t *hashBox, int oddevenInput, const size_t capacity) {
    // Consts:
    const double golden = 1.61803398;
    const double euler = 2.71828;
    const double plack = 6.62606;
    const double avogrado = 6.02214;
    const double feigenbaum = 4.669201;
    const double fine_structure = 7.29735;

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
