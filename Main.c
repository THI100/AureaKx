#include <stdio.h>
#include <stdint.h>
#include <string.h>

//structs:

typedef struct uint128_t {
    uint64_t low;
    uint64_t high;
} uint128_t;

struct hash1024 {
    uint128_t first;
    uint128_t second;
    uint128_t third;
    uint128_t forth;
    uint128_t fifth;
    uint128_t sixth;
    uint128_t seventh;
    uint128_t eight;
};

//typedefs:

//enums:

//functions:
void encode (char input);
void dupper (char input);

//main:
int main () {
    char input[128];

    printf("Enter input: ");
    scanf(" %s", &input);

    size_t sizeInput = strlen(input);

    printf("%lld /n", sizeInput);

    if (sizeInput == 0) {
        printf("error: you didnt give any input!");
    }
    else if (sizeInput >= 16) {
        printf("major cloning in work.");
    }
    else if (sizeInput < 16) {
        printf("cloning in work.");
    }
    else {
        printf("error, your input is too large.");
    }


    return 0;
}

void encode (char input) {

}

void dupper (char input) {}