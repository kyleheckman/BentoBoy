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

    int test = atoi(argv[1]);
    uint8_t flags_test = (uint8_t)atoi(argv[3]);

    if (test == 1) {        /*dec_8 test*/
        regs[0] = (uint8_t)atoi(argv[2]);
        uint8_t old = regs[0];
        dec_8(&regs[0], &flags);

        if (regs[0] == (uint8_t)(old - 1) && flags == flags_test) {
            return 0;
        }
        return 1;
    }
    else if (test == 2) {   /*dec_16 test*/
        uint16_t old = (uint16_t)atoi(argv[2]);
        regs[1] = old>>8;
        regs[2] = old;
        dec_16(&regs[1]);

        if ((uint16_t)((regs[1] << 8) + regs[2]) == (uint16_t)(old - 1)) {
            return 0;
        }
        return 1;
    }
    return 1;
}