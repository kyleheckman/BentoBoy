#pragma once
#include <stdint.h>

/*--------------------------------------------------*/
/* Execute given opcode */
int exec_instr(uint8_t opcode, uint8_t* regs, uint8_t* ram, uint8_t* flags, uint16_t* sp, uint16_t* pc);

int exec_cb(uint8_t opcode, uint8_t* regs, uint8_t* ram, uint8_t* flags, uint16_t* sp, uint16_t* pc);