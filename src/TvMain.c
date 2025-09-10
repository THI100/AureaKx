#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#include "../include/AureaKx"

int main() {

    char testhash[256] = hash("0", 64, 16);
    printf("tested function output: %s", testhash);
    free(testhash);

    return 0;
}