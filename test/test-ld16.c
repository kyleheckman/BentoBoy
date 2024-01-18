#include "gb_isa.h"
#include <stdint.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char** argv)
{
    uint8_t regs[7];
    memset(regs, 0, 7);

    uint16_t val = (uint16_t)atoi(argv[1]);
    ld_16(&regs[1], val);

    uint16_t tmp = (regs[1]<<8) + regs[2];
    if (tmp == val) {
        return 0;
    }
    return 1;
}