#include <string.h>
#include <stdint.h>
#include <math.h>

#include "../Logics.h"

void bloomHash(int Temp1, int Temp2, uint8_t *tempBox, size_t capacity);

void logicOpps(uint8_t *hashBox, uint32_t oddevenInput, const size_t capacity) {
    uint8_t tempBox[capacity];
    memcpy(tempBox, hashBox, capacity);

    for (size_t i = 0; i < (capacity / 2); i++) {
        int Temp1 = tempBox[i];
        int Temp2 = tempBox[(i * oddevenInput) % capacity];

        switch (i % 64) {
            case 0:  tempBox[i] = Temp1 ^ Temp2; break;
            case 1:  tempBox[i] = Temp1 & Temp2; break;
            case 2:  tempBox[i] = ~(Temp1 & Temp2); break;
            case 3:  tempBox[i] = ~(Temp1 | Temp2); break;
            case 4:  tempBox[i] = Temp1 | Temp2; break;
            case 5:  tempBox[i] = (Temp1 ^ Temp2) & 0xFF; break;
            case 6:  tempBox[i] = (Temp1 & ~Temp2); break;
            case 7:  tempBox[i] = (Temp2 & ~Temp1); break;
            case 8:  tempBox[i] = ((Temp1 << 1) | (Temp1 >> 7)) & 0xFF; break;
            case 9:  tempBox[i] = ((Temp2 >> 1) | (Temp2 << 7)) & 0xFF; break;
            case 10: tempBox[i] = ~(Temp1 ^ Temp2); break;
            case 11: tempBox[i] = (Temp1 + Temp2) & 0xFF; break;
            case 12: tempBox[i] = (Temp1 - Temp2) & 0xFF; break;
            case 13: tempBox[i] = (Temp1 | Temp2) ^ (Temp1 & Temp2); break;
            case 14: tempBox[i] = (Temp1 >> 2) | (Temp2 << 6); break;
            case 15: tempBox[i] = (Temp1 ^ (Temp2 << 1)) & 0xFF; break;
            case 16: tempBox[i] = (Temp1 & Temp2) | (Temp1 ^ Temp2); break;
            case 17: bloomHash(Temp1, Temp2, tempBox, capacity); break;
            case 18: tempBox[i] = ~(Temp1) ^ Temp2; break;
            case 19: tempBox[i] = (Temp1 * 3 + Temp2 * 7) & 0xFF; break;
            case 20: tempBox[i] = ((Temp1 << 3) ^ (Temp2 >> 2)) & 0xFF; break;
            case 21: tempBox[i] = ((Temp1 + 1) ^ (Temp2 - 1)) & 0xFF; break;
            case 22: tempBox[i] = (Temp1 ^ (0xAA)) & Temp2; break;
            case 23: tempBox[i] = ((Temp2 * Temp2) ^ Temp1) & 0xFF; break;
            case 24: tempBox[i] = (~(Temp1 >> 1) + (Temp2 << 2)) & 0xFF; break;
            case 25: tempBox[i] = ((Temp1 | Temp2) << 1) & 0xFF; break;
            case 26: tempBox[i] = ((Temp1 & 0x0F) << 4) | ((Temp2 & 0xF0) >> 4); break;
            case 27: tempBox[i] = (Temp1 * Temp2 + i) & 0xFF; break;
            case 28: tempBox[i] = ((Temp1 << (i % 8)) | (Temp2 >> (8 - (i % 8)))) & 0xFF; break;
            case 29: tempBox[i] = ((Temp2 << 2) - (Temp1 >> 1)) & 0xFF; break;
            case 30: tempBox[i] = ((Temp1 ^ Temp2 ^ i) + 42) & 0xFF; break;
            case 31: tempBox[i] = ((Temp1 & Temp2) ^ 0x5A); break;
            case 32: tempBox[i] = (Temp1 ^ 0x3C) + (Temp2 ^ 0xC3); break;
            case 33: tempBox[i] = ((~(Temp1 ^ Temp2)) + i) & 0xFF; break;
            case 34: tempBox[i] = (Temp1 + (Temp2 ^ 0xFF)) & 0xFF; break;
            case 35: tempBox[i] = ((Temp1 >> 3) + (Temp2 << 5)) & 0xFF; break;
            case 36: tempBox[i] = ((Temp1 * 13) ^ (Temp2 * 17)) & 0xFF; break;
            case 37: tempBox[i] = ((Temp1 | ~Temp2) + 91) & 0xFF; break;
            case 38: tempBox[i] = (Temp1 ^ Temp2 ^ (i * 31)) & 0xFF; break;
            case 39: tempBox[i] = (Temp1 & Temp2 & i) | (Temp1 ^ Temp2); break;
            case 40: tempBox[i] = ((Temp1 << 2) ^ (Temp2 >> 2)) & 0xFF; break;
            case 41: tempBox[i] = ((Temp1 + Temp2 + i) * 7) & 0xFF; break;
            case 42: tempBox[i] = ((Temp1 | i) ^ (Temp2 & i)) & 0xFF; break;
            case 43: tempBox[i] = ((Temp1 & Temp2) + (Temp1 | Temp2)) & 0xFF; break;
            case 44: tempBox[i] = (((Temp1 + Temp2) >> 1) ^ Temp1) & 0xFF; break;
            case 45: tempBox[i] = ((Temp1 * Temp2) ^ (Temp1 + Temp2)) & 0xFF; break;
            case 46: tempBox[i] = ((Temp1 * 2) + (Temp2 * 3)) ^ i; break;
            case 47: tempBox[i] = ((Temp1 & 0xAA) | (Temp2 & 0x55)) ^ i; break;
            case 48: tempBox[i] = ((Temp1 << 1) + (Temp2 << 2)) & 0xFF; break;
            case 49: tempBox[i] = ((Temp1 * Temp1) - (Temp2 * Temp2)) & 0xFF; break;
            case 50: tempBox[i] = (((Temp1 ^ Temp2) >> 1) + 128) & 0xFF; break;
            case 51: tempBox[i] = (((Temp1 & Temp2) << 1) | (Temp1 ^ Temp2)) & 0xFF; break;
            case 52: tempBox[i] = (Temp1 ^ Temp2 ^ 0xDE) & 0xFF; break;
            case 53: tempBox[i] = (((Temp1 + 13) * (Temp2 + 29)) >> 2) & 0xFF; break;
            case 54: tempBox[i] = ((Temp1 * 11) ^ (Temp2 * 19) + i) & 0xFF; break;
            case 55: tempBox[i] = (((Temp1 << 1) | (Temp2 >> 1)) ^ i) & 0xFF; break;
            case 56: tempBox[i] = ((Temp1 & Temp2) ^ (~Temp1 | Temp2)) & 0xFF; break;
            case 57: tempBox[i] = ((Temp1 + Temp2 + i) ^ (Temp1 * Temp2)) & 0xFF; break;
            case 58: tempBox[i] = (((Temp1 >> 1) + (Temp2 << 1)) ^ i) & 0xFF; break;
            case 59: tempBox[i] = ((Temp1 ^ Temp2) + (i * 37)) & 0xFF; break;
            case 60: tempBox[i] = ((~Temp1 & Temp2) | (Temp1 & ~Temp2)) & 0xFF; break;
            case 61: tempBox[i] = (Temp1 ^ ((Temp2 + i) * 5)) & 0xFF; break;
            case 62: tempBox[i] = ((Temp1 << (i % 4)) ^ (Temp2 >> (i % 4))) & 0xFF; break;
            case 63: tempBox[i] = (((Temp1 ^ i) + (Temp2 * 2)) >> 1) & 0xFF; break;
            default: return;
        }
    }

    memcpy(hashBox, tempBox, capacity);
}

void logMathOpps(uint8_t *hashBox, uint32_t oddevenInput, const size_t capacity) {
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
        int Temp2 = tempBox[(i * oddevenInput) % capacity];
        double result = 0;

        switch (i % 10) {
            case 0:
                result = fmod(Temp1 * golden + Temp2, 256);
                break;
            case 1:
                result = fmod(pow(euler, fmod(Temp1, 5)) + Temp2, 256);
                break;
            case 2:
                result = fmod((Temp1 * Temp2 * feigenbaum), 256);
                break;
            case 3:
                result = fmod(log(Temp1 + 1) * plack + Temp2, 256);
                break;
            case 4:
                result = fmod((sin(Temp1) + cos(Temp2)) * avogrado, 256);
                break;
            case 5:
                result = fmod((Temp1 ^ Temp2) * fine_structure, 256);
                break;
            case 6:
                result = fmod(pow((Temp1 + 1), 2.2) + pow((Temp2 + 1), 1.7), 256);
                break;
            case 7:
                result = fmod((Temp1 * golden * feigenbaum) - (Temp2 * plack), 256);
                break;
            case 8:
                result = fmod(log((Temp1 | 1)) * pow(euler, (Temp2 % 3)), 256);
                break;
            case 9:
                result = fmod((Temp1 * Temp1 + Temp2 * Temp2) / (fine_structure + 1), 256);
                break;
            default: return;
        }

        tempBox[i] = (uint8_t)((int)result & 0xFF);
    }

    memcpy(hashBox, tempBox, capacity);
}


void bloomHash(int Temp1, int Temp2, uint8_t *tempBox, size_t capacity) {
    uint8_t mix = (uint8_t)((Temp1 ^ Temp2) + (Temp1 | Temp2));
    for (size_t i = 0; i < capacity; i++) {
        tempBox[i] ^= ((mix << (i % 8)) | (mix >> (8 - (i % 8)))) & 0xFF;
        tempBox[i] = ((tempBox[i] * 33) ^ (mix + i)) & 0xFF;
    }
}
