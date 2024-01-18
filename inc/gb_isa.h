#pragma once
#include <stdint.h>

/* instruction execution */
/*--------------------------------------------------*/
int exec_instr(uint8_t opcode);

/* fetch instructions from program counter */
/*--------------------------------------------------*/
uint8_t fetch8(uint8_t* ram, uint16_t* pc);

uint16_t fetch16(uint8_t* ram, uint16_t* pc);

/* helper functions */
/*--------------------------------------------------*/
uint8_t* deref(uint8_t* ram, uint8_t high, uint8_t low);

/* ISA functions */

/* load & move instructions */
/*--------------------------------------------------*/
void ld_8(uint8_t* dest, uint8_t src);

void ld_16(uint8_t* dest, uint16_t val);

/* arithmetic instructions */
/*--------------------------------------------------*/
/* increment & decrement */
void inc_8(uint8_t* dest, uint8_t* flags);

void inc_16(uint8_t* dest);

void dec_8(uint8_t* dest, uint8_t* flags);

void dec_16(uint8_t* dest);

/* add & subtract */
void add_16(uint8_t* dest, uint8_t* src, uint8_t* flags);

/* bitwise functions */
/*--------------------------------------------------*/
/* bitwise rotate */
void rlca();

void rrca();