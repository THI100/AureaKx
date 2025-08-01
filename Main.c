#include <stdio.h>
#include <stdint.h>
#include <string.h>

// -------------------------------------- Structs ----------------------------------------- \\

struct hash1024 {
    uint8_t hexbox[128];
    uint16_t hid;
};

// --------------------- Function Prototypes --------------------- \\

void charsToHex(const char *input, int length, uint8_t *hexBox);
void cloner(uint8_t *hexBox, int length, int capacity);

// -------------------------------- Main ----------------------------------- \\

int main() {
    const int limit = 128;
    char input[128];
    uint8_t convertedHex[128];

    printf("Enter input: ");
    scanf(" %127s", input);

    size_t sizeInput = strlen(input);
    printf("Input size: %zu\n", sizeInput);

    charsToHex(input, sizeInput, convertedHex);
    cloner(convertedHex, sizeInput, limit);

    printf("Hex output:\n");
    for (int i = 0; i < limit; i++) {
        printf("0x%02X ", convertedHex[i]);
        if ((i + 1) % 16 == 0) printf("\n");
    }

    return 0;
}

// ---------------------------- Functions -------------------------------- \\

void charsToHex(const char *input, int length, uint8_t *hexBox) {
    for (int i = 0; i < length; i++) {
        hexBox[i] = (uint8_t)input[i];  // Safe cast
    }
}

void cloner(uint8_t *hexBox, int length, int capacity) {
    const int goldenShuffler = 1618033;
    const int eulerShuffler = 57721;
    const uint8_t container[] = {
        0x21, 0x22, 0x23, 0x24, 0x25, 0x26, 0x27, 0x28, 0x29, 0x2A,
        0x2B, 0x2C, 0x2D, 0x2E, 0x2F, 0x30, 0x31, 0x32, 0x33, 0x34,
        0x35, 0x36, 0x37, 0x38, 0x39, 0x3A, 0x3B, 0x3C, 0x3D, 0x3E,
        0x3F, 0x40, 0x41, 0x42, 0x43, 0x44, 0x45, 0x46, 0x47, 0x48,
        0x49, 0x4A, 0x4B, 0x4C, 0x4D, 0x4E, 0x4F, 0x50
    };
    const int container_size = sizeof(container) / sizeof(container[0]);

    for (int j = length; j < capacity; j++) {
        // int ind = j % container_size;
        hexBox[j] = container[ind];
    }
}
