#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#include "../include/AureaKx.h"

int main() {
    char input[2] = "r4";

    // Change the declaration to a single pointer
    char *testhash = hash(input, 64, 16);
    
    // Check if hash returned NULL
    if (testhash == NULL) {
        fprintf(stderr, "Error: hash function returned NULL\n");
        return 1; // Exit with an error code
    }

    printf("tested function output: %s\n", testhash);
    
    // Free the memory allocated by hash
    free(testhash);

    return 0;
}