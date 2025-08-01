#include <stdio.h>
#include <stdint.h>
#include <string.h>

//structs:

struct hash1024 {
    uint8_t hexbox[128];
    uint16_t hid;
};

//typedefs:

//enums:

//functions:
void charsToHex(const char *input, int length, uint8_t *hexBox);
void dupper (char input);

//main:
int main () {
    const char input[256];
    uint8_t convertedHex[128];

    printf("Enter input: ");
    scanf(" %s", &input);

    size_t sizeInput = strlen(input);
    printf("%lld \n", sizeInput);

    charsToHex (input, sizeInput, convertedHex);

    printf ("Finished \n");

    for (int i = 0; i < sizeInput; i++) {
        printf("0x%02X \n", convertedHex[i]);
    }

    // End point
    return 0;
}

void charsToHex(const char *input, int length, uint8_t *hexBox) {
    for (int i = 0; i < length; i++) {
        hexBox[i] = (unsigned char)input[i];
    }
}

void dupper (char input) {}