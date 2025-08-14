#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>

// ------------------------------- Intern Libraries --------------------------------- \\

#include "../Internal_dependencies/Shufflers.h"
#include "../Internal_dependencies/Solutioners.h"
#include "../Internal_dependencies/Logics.h"

// -------------------------------- Main ----------------------------------- \\

int main() {
    // consts:
    const size_t limit = 128;    // hash size in bytes
    const size_t buffer = 4096;  // input buffer size
    const int generalRounds = 64;

    // non-consts:
    char input[buffer];
    uint8_t input_hex_array[buffer];
    uint8_t hash[limit];

    memset(hash, 0, limit);

    // open input file for reading
    FILE *input_file = fopen("To_make_keys.txt", "r");
    if (!input_file) {
        perror("Error opening input file");
        return 1;
    }

    // safe read
    if (!fgets(input, sizeof(input), input_file)) {
        perror("Error reading input file");
        fclose(input_file);
        return 1;
    }
    fclose(input_file);

    // remove newline if present
    size_t len = strlen(input);
    if (len > 0 && input[len - 1] == '\n') {
        input[len - 1] = '\0';
        len--;
    }

    size_t sizeInput = len;

    // Convert to hex array
    converter(input, sizeInput, input_hex_array);

    // Calculate odd/even flag
    uint32_t sumHash = 0;
    for (size_t i = 0; i < sizeInput; i++) {
        sumHash += input_hex_array[i];
    }
    uint32_t oeInput = sumHash % 2;

    // Fill or compact input into hash
    if (sizeInput < limit) {
        autoFill(input_hex_array, sizeInput, limit, hash);
    } else if (sizeInput == limit) {
        memcpy(hash, input_hex_array, limit);
    } else {
        compactor(input_hex_array, sizeInput, limit, hash);
    }

    // Processing chain
    differentiator(hash, limit);
    goldenShuffler(hash, limit, generalRounds);
    logicOpps(hash, oeInput, limit);
    corrector(hash, limit, input_hex_array, sizeInput);
    logMathOpps(hash, oeInput, limit);
    eulerShuffler(hash, limit, generalRounds);
    differentiator(hash, limit);
    corrector(hash, limit, input_hex_array, sizeInput);

    // Convert hash to hex string
    char hash_str[limit * 2 + 1];
    for (size_t i = 0; i < limit; i++) {
        sprintf(hash_str + (i * 2), "%02x", hash[i]);
    }
    hash_str[limit * 2] = '\0';

    // write output file
    FILE *output_file = fopen("Keys.txt", "w");
    if (!output_file) {
        perror("Error opening output file");
        return 1;
    }
    fprintf(output_file, "%s\n", hash_str);
    fclose(output_file);

    // also print for verification
    printf("Hash: %s\n", hash_str);

    return 0;
}
