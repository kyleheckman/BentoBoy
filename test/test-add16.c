#include "gb_isa.h"
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char** argv)
{
    uint8_t regs[7];
    uint8_t flags = 0;
    memset(regs, 0, 7);

    uint8_t flags_test = (uint8_t)atoi(argv[3]);

    uint16_t a = (uint16_t)atoi(argv[1]);
    regs[1] = a>>8;
    regs[2] = a;

    uint16_t b = (uint16_t)atoi(argv[2]);
    regs[3] = b>>8;
    regs[4] = b;

    printf("REGS B %hhd C %hhd D %hhd E %hhd\n\r", regs[1], regs[2], regs[3], regs[4]);

    add_16(&regs[1], &regs[3], &flags);

    printf("B %hhd C %hhd FLAGS %hhd FT %hhd\n\r",regs[1], regs[2], flags, flags_test);

    if (((regs[1] << 8) + regs[2] == (uint16_t)(a + b)) && flags == flags_test) {
        return 0;
    }
    return 1;
}