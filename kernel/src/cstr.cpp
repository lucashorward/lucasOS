#include "cstr.h"

char intToStringOutput[128];
const char* to_string(uint64_t value) {
    uint8_t size;
    uint64_t sizeTest = value;
    while (sizeTest / 10 > 0) {
        sizeTest /= 10;
        size++;
    }

    uint8_t index = 0;
    while(value / 10 > 0) {
        uint8_t remainder = value % 10;
        value /= 10;
        intToStringOutput[size - index] = remainder + '0';
        index++;
    }

    uint8_t remainder = value % 10;
    intToStringOutput[size - index] = remainder + '0';
    intToStringOutput[size + 1] = 0;
    return intToStringOutput;
}