#include "gb_isa.h"
#include "gb_opcodes.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define RAM_SIZE (1 << 10) * 64     /* 64KB memory*/
#define HRAM 0xff80
#define WRAM 0xc000
#define VRAM 0x8000

int main(int argc, char** argv)
{
    uint8_t regs[7];
    uint8_t ram[RAM_SIZE];
    memset(regs, 0, 7);
    memset(ram, 0, RAM_SIZE);

    uint8_t flags = 0;
    uint16_t sp = 0xfffe;       /* Note: stack shares same memory region as high mem (HRAM) */
    uint16_t pc = 0;            /* set program counter to 0 */


}