#include <stdio.h>
#include <stdint.h>

void encode (char* input, uint64_t* output);

int main () {
    const char input = "/0";

    printf ("Put a short message to be encrypted:");
    scanf("%s", input);

    return 0;
}

void encode (const char* input, uint64_t* output) {

}