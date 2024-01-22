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

int main(int argc, char** argv)
{
    uint8_t regs[8];
    uint8_t ram[RAM_SIZE];
    memset(regs, 0, 8);
    memset(ram, 0, RAM_SIZE);

    uint16_t sp = STACK_HEAD;   /* Note: stack shares same memory region as high mem (HRAM) */
    uint16_t pc = PROG_START;   /* set program counter entry point */


}