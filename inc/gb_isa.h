#pragma once
#include <stdint.h>

/* fetch instructions from program counter */
/*--------------------------------------------------*/
uint8_t fetch8(uint8_t* ram, uint16_t* pc);

uint16_t fetch16(uint8_t* ram, uint16_t* pc);

/* helper functions */
/*--------------------------------------------------*/
uint8_t* deref(uint8_t* ram, uint8_t high, uint8_t low);

/* ISA functions */

/* jump instructions */
/*--------------------------------------------------*/
void jp(uint16_t dest, uint16_t* pc, uint8_t* flags, int cond);

void jr(uint16_t dest, uint16_t* pc uint8_t* flags, int cond);

void call(uint16_t dest, uint16_t* pc uint16_t* sp, uint8_t* flags, int cond);

void ret(uint16_t* pc, uint16_t* sp, uint8_t* ram, uint8_t* flags, int cond);

void rst(uint16_t* pc, uint16_t *sp, uint8_t* ram, int cond);

/* load & move instructions */
/*--------------------------------------------------*/
void ld_8(uint8_t* dest, uint8_t src);

void ld_16(uint8_t* dest, uint16_t val);

void ld_sp(uint16_t* sp, uint16_t val);

void push(uint8_t* src, uint16_t* sp, uint8_t* ram);

void pop(uint8_t* dest, uint16_t* sp, uint8_t* ram);

/* arithmetic instructions */
/*--------------------------------------------------*/
/* increment & decrement */
void inc_8(uint8_t* dest, uint8_t* flags);

void inc_16(uint8_t* dest);

void dec_8(uint8_t* dest, uint8_t* flags);

void dec_16(uint8_t* dest);

/* add & subtract */
void add_8(uint8_t* dest, uint8_t src, int adc, uint8_t* flags);

void add_16(uint8_t* dest, uint8_t* src, uint8_t* flags);

void add_sp_to(uint8_t* dest, uint16_t sp, uint8_t* flags);

void add_to_sp(uint16_t* sp, int8_t operand, uint8_t* flags);

void sub_8(uint8_t* dest, uint8_t src, int sbc, uint8_t* flags);

/* bitwise functions */
/*--------------------------------------------------*/
/* logical operations */
void land(uint8_t* dest, uint8_t src, uint8_t* flags);

void lxor(uint8_t* dest, uint8_t src, uint8_t* flags);

void lor(uint8_t* dest, uint8_t src, uint8_t* flags);

void lcp(uint8_t dest, uint8_t src, uint8_t* flags);

/* bitwise rotate */
void rlc(uint8_t* regs, int r, uint8_t* flags);

void rrc(uint8_t* regs, int r, uint8_t* flags);