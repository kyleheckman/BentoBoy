#include "gb_isa.h"
#include <stdint.h>
#include <string.h>
#include <stdlib.h>

#include <stdio.h>

int main (int argc, char** argv) {
    uint8_t ram[1024];
    uint8_t regs[8];
    memset(ram, 0, 1024);
    memset(regs, 0, 8);

    uint16_t sp = 1000;
    uint16_t test[16];
    memset(test, 0, 16*sizeof(uint16_t));

    if (atoi(argv[1]) == 1) {
        int count = argc-2;
        int i = 0;
        for (i = 2; i < argc; i++) {
            ld_16(&regs[2], (uint16_t)atoi(argv[i]));
            test[i-2] = (uint16_t)atoi(argv[i]);
            push(&regs[2], &sp, ram);
        }

        if (1000-sp != 2*count) {return 4;}
        /*for (i = 0; i < count; i++) {
            printf("TEST[%d] %d\n\r",i,test[i]);
        }*/
        for (i = 0; i < count; i++) {
            /*printf("RAM[SP] %d | RAM[SP+1] %d | TEST %d\n\r", ram[sp+2*i], ram[sp+1+2*i], test[count-i-1]);*/
            uint16_t val = ram[sp+2*i] + (ram[sp+1+2*i] << 8);
            if (val != test[count-i-1]) {return 1;}
        }
        return 0;
    }
}