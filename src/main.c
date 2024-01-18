#include "gb_isa.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char** argv)
{
    uint8_t regs[7];
    memset(regs, 0, 7);

    printf("A: %hhd ", regs[0]);
    printf("B: %hhd\n\r", regs[1]);

    regs[1] = (uint8_t)atoi(argv[1]);
    ld_8(&regs[0], regs[1]);

    printf("A: %hhd ", regs[0]);
    printf("B: %hhd\n\r", regs[1]);

    return 0;
}