#include "gb_isa.h"
#include "gb_opcodes.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define RAM_SIZE (1 << 10) * 64     /* 64KB memory*/
#define HRAM 0xff80
#define WRAM 0xc000
#define VRAM 0x8000
#define PROG_START 0x150
#define STACK_HEAD 0xfffe

/* first passed argument should be the filename of the ROM to load */
int main(int argc, char** argv)
{
    uint8_t regs[8];
    uint8_t ram[RAM_SIZE];
    memset(regs, 0, 8);
    memset(ram, 0, RAM_SIZE);

    uint16_t sp = STACK_HEAD;   /* Note: stack shares same memory region as high mem (HRAM) */
    uint16_t pc = PROG_START;   /* set program counter entry point */

    if(argc < 2) {
        printf("No ROM file provided... Exiting...\n\r");
        return -1;
    } /* ROM argument not given */
    
    FILE *gb_rom = fopen(argv[1], "r");
    if (!gb_rom) {
        printf("Failed to open %s... Exiting...\n\r",argv[1]);
        return -1;
    }

    printf("Reading %s...\n\r", argv[1]);

    /* load file into RAM at PROG_START */
    if(!fgets(&ram[PROG_START], 127, gb_rom)) {
        printf("Read Failed... Exiting...\n\r");
        return -1;
    }

    fclose(gb_rom);

    printf("| %s |\n\r", &ram[PROG_START]);

    /* test of reading opcode functions, ends on NULL op */
    /* NULL op is used for NOP and CB->rlc, not intended to test this functionality */
    uint8_t op = ram[pc];
    int errno = 0;
    while (op) {
        errno = exec_instr(op, regs, ram, &sp, &pc);
        pc++;
        op = ram[pc];
        if (errno) {
            printf("ERROR CODE: %d | Exiting application...\n\r", errno);
            break;
        }
    }

    printf("REGS: A|%hhd, B|%hhd, C|%hhd, D|%hhd, E|%hhd, H|%hhd, L|%hhd\n\r", regs[0], regs[2], regs[3], regs[4], regs[5], regs[6], regs[7]);

    return 0;
}