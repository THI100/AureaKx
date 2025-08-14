#ifndef SOLUTIONERS_H
#define SOLUTIONERS_H

void converter(const char *input, size_t length, uint8_t *hexBox);
void autoFill(const uint8_t *hexBox, size_t length, size_t capacity, uint8_t *hashBoxH);
void compactor (const uint8_t *hexBox, size_t length, size_t capacity, uint8_t *hashBoxH);
void differentiator(uint8_t *hashBox, size_t capacity);
void weakIndexCorrector(uint8_t *hashBox, size_t capacity, uint8_t *inputOriginal, size_t sizeOriginal);

#endif //SOLUTIONERS_H
