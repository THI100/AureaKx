#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <math.h>
#include <tgmath.h>

// -------------------------------------- Structs ----------------------------------------- \\

struct hash1024 {
    uint8_t hexBox[128];
    uint16_t id;
};

// --------------------- Function Prototypes --------------------- \\

void converter(const char *input, size_t length, uint8_t *hexBox);
void autoFill(const uint8_t *hexBox, size_t length, size_t capacity, uint8_t *hashBoxH);
void compactor (const uint8_t *hexBox, size_t length, size_t capacity, uint8_t *hashBoxH);
void goldenShuffler(uint8_t *hashBox, size_t capacity, int rounds);
void eulerShuffler();
void differentiator();

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

    goldenShuffler(hashBox, limit, generalRounds);


    printf("\n\n\n Hex output:\n");
    for (int i = 0; i < limit; i++) {
        printf("0x%02X ", hashBox[i]);
        if ((i + 1) % 16 == 0) printf("\n");
    }

    return 0;
}

// ---------------------------- Functions -------------------------------- \\

void converter(const char *input, size_t length, uint8_t *hexBox) {
    memcpy(hexBox, input, length);
}

void autoFill(const uint8_t *hexBox, size_t length, const size_t capacity, uint8_t *hashBoxH) {

    const uint8_t container_ASCII[] = {
        0x21, 0x22, 0x23, 0x24, 0x25, 0x26, 0x27, 0x28, 0x29,
        0x2A, 0x2B, 0x2C, 0x2D, 0x2E, 0x2F, 0x30, 0x31, 0x32, 0x33,
        0x34, 0x35, 0x36, 0x37, 0x38, 0x39, 0x3A, 0x3B, 0x3C, 0x3D,
        0x3E, 0x3F, 0x40, 0x41, 0x42, 0x43, 0x44, 0x45, 0x46, 0x47,
        0x48, 0x49, 0x4A, 0x4B, 0x4C, 0x4D, 0x4E, 0x4F, 0x50, 0x51,
        0x52, 0x53, 0x54, 0x55, 0x56, 0x57, 0x58, 0x59, 0x5A, 0x5B,
        0x5C, 0x5D, 0x5E, 0x5F, 0x60, 0x61, 0x62, 0x63, 0x64, 0x65,
        0x66, 0x67, 0x68, 0x69, 0x6A, 0x6B, 0x6C, 0x6D, 0x6E, 0x6F,
        0x70, 0x71, 0x72, 0x73, 0x74, 0x75, 0x76, 0x77, 0x78, 0x79,
        0x7A, 0x7B, 0x7C, 0x7D, 0x7E
    };
    int container_size = sizeof(container_ASCII) / sizeof(container_ASCII[0]);

    memcpy(hashBoxH, hexBox, length);

    // semi-Perfection (just doubles one-time the same ASCII):
    for (size_t j = length; j < capacity; j++) {
        double goldenM = ((1.618*(j/3.74)) * j);
        int gMR = round(goldenM);

        if (gMR < container_size) {
            int selected = container_ASCII[gMR % container_size];
            hashBoxH[j] = selected;
        }
        else {
            int temp = hashBoxH[(j * gMR) % length];
            int selected = container_ASCII[((temp * gMR) % j) % container_size];
            hashBoxH[j] = selected;
        }
    }
}

void compactor(const uint8_t *hexBox, size_t length, const size_t capacity, uint8_t *hashBoxH) {
    // Temporary buffer to work on
    uint8_t tempBox[length];
    memcpy(tempBox, hexBox, length);
    size_t currentLength = length;

    // Reducing until 128 items
    while (currentLength > capacity) {
        size_t newLength = 0;
        for (size_t i = 0; i < currentLength; i += 2) {
            uint16_t sum = tempBox[i];
            if (i + 1 < currentLength) {
                sum += tempBox[i + 1];
            }
            // moderator
            uint8_t reduced = (sum > 127) ? (sum % 127) : sum;
            tempBox[newLength++] = reduced;
        }
        currentLength = newLength;
    }

    // Passing temp to hash
    memcpy(hashBoxH, tempBox, capacity);
}

void goldenShuffler(uint8_t *hashBox, const size_t capacity, const int rounds) {
    const double goldenR = 1.618;
    uint8_t tempBox[capacity];
    memcpy(tempBox, hashBox, capacity);

    for (int i = 0; i < rounds; i++) {
        double gR = goldenR * (i*i);
        int gMR = round(gR);
        uint8_t Temp1 = tempBox[gMR % capacity];
        tempBox[(i*2) % capacity] = Temp1;
    }

    memcpy(hashBox, tempBox, capacity);
}

void eulerShuffler() {
    printf("In construction\n");
}

void differentiator() {
    printf("In construction\n");
}
