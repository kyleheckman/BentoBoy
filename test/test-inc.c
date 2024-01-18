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
    regs[0] = (uint8_t)atoi(argv[2]);
    uint8_t flags_test = (uint8_t)atoi(argv[3]);

    if (test == 1) {    /*inc_8 test*/
        uint8_t old = regs[0];
        inc_8(&regs[0], &flags);

        /*printf("OLD %hhd INC %hhd FLAGS %hhd FT %hhd\n\r",old, regs[0], flags, flags_test);*/

        if (regs[0] == (uint8_t)(old + 1) && flags == flags_test) {
            return 0;
        }
        return 1;
    }
}