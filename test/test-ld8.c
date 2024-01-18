#include "gb_isa.h"
#include "test-ld8.h"
#include <stdint.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char** argv)
{
    uint8_t regs[7];
    memset(regs, 0, 7);

    int test = atoi(argv[1]);

    if (test == 1) {
        regs[1] = (uint8_t)atoi(argv[2]);
        ld_8(&regs[0], regs[1]);

        if (regs[0] == regs[1]) {
            return 0;
        }
        return 1;
    }
    else {
        uint16_t val = (uint16_t)atoi(argv[2]);
        ld_16(&regs[0], val);

        uint16_t tmp = (regs[0] << 8) + regs[1];
        if (tmp == val) {
            return 0;
        }
        return 1;
    }
}