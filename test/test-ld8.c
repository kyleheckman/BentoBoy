#include "gb_isa.h"
#include <stdint.h>
#include <string.h>
#include <stdlib.h>

#define RAM_SIZE (1<<10) * 4

int main(int argc, char** argv)
{
    uint8_t regs[7];
    uint8_t ram[RAM_SIZE];
    memset(regs, 0, 7);
    memset(ram, 0x5a, RAM_SIZE);

    int test = atoi(argv[1]);

    if (test == 1) {    /*Move value REG->REG*/
        regs[1] = (uint8_t)atoi(argv[2]);
        ld_8(&regs[0], regs[1]);

        if (regs[0] == regs[1]) {
            return 0;
        }
        return 1;
    }
    else if (test == 2) {   /*Copy val to memory*/
        regs[0] = (uint8_t)atoi(argv[2]);
        regs[2] = 0x80;
        ld_8(deref(ram, regs[1], regs[2]), regs[0]);

        if (regs[0] == ram[0x80]) {
            return 0;
        }
        return 1;
    }
    else if (test == 3) {   /*Store immediate value into REG*/
        uint8_t val = (uint8_t)atoi(argv[2]);
        ld_8(&regs[1], val);

        if (regs[1] == val) {
            return 0;
        }
        return 1;
    }
    else if (test == 4) {   /*Copy val from mem to REG*/
        uint8_t addr = (uint8_t)atoi(argv[2]);
        regs[2] = addr;
        ram[addr] = 0x64;
        ld_8(&regs[0], *deref(ram, regs[1], regs[2]));

        if (regs[0] == ram[addr]) {
            return 0;
        }
        return 1;
    }

    return 1;
}