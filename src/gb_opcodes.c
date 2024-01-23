#include "gb_isa.h"
#include "gb_opcodes.h"

/* REGS:    0:A | 1:B | 2:C | 3:D | 4:E | 5:H | 6:L */
#define rA 0
#define FL 1
#define rB 2
#define rC 3
#define rD 4
#define rE 5
#define rH 6
#define rL 7

int exec_instr(uint8_t opcode, uint8_t* regs, uint8_t* ram, uint16_t* sp, uint16_t* pc) {
	uint16_t tmp_val = 0;
        switch (opcode)
	{
        case 0: break;	 /* NOP */
        case 0x01: ld_16(&regs[rB], fetch16(ram, pc)); break;
        case 0x02: ld_8(deref(ram, regs[rB], regs[rC]), regs[rA]); break;
        case 0x03: inc_16(&regs[rB]); break;
        case 0x04: inc_8(&regs[rB], &regs[FL]); break;
        case 0x05: dec_8(&regs[rB], &regs[FL]); break;
        case 0x06: ld_8(&regs[rB], fetch8(ram, pc)); break;
        case 0x07: rlc(&regs[rA], 1, &regs[FL]); break;
        case 0x08: ld_16(deref(ram, fetch8(ram, pc), fetch8(ram, pc)), *sp); break;
        case 0x09: add_16(&regs[rH], &regs[rB], &regs[FL]); break;
        case 0x0a: ld_8(&regs[rA], *deref(ram, regs[rB], regs[rC])); break;
        case 0x0b: dec_16(&regs[rB]); break;
        case 0x0c: inc_8(&regs[rC], &regs[FL]); break;
        case 0x0d: dec_8(&regs[rC], &regs[FL]); break;
        case 0x0e: ld_8(&regs[rC], fetch8(ram, pc)); break;
        case 0x0f: rrc(&regs[rA], 1, &regs[FL]); break;
        /*-------------------------------------------------------*/
        case 0x10: return -1; /* STOP, not implemented */
        case 0x11: ld_16(&regs[rD], fetch16(ram, pc)); break;
        case 0x12: ld_8(deref(ram, regs[rD], regs[rE]), regs[rA]); break;
        case 0x13: inc_16(&regs[rD]); break;
        case 0x14: inc_8(&regs[rD], &regs[FL]); break;
        case 0x15: dec_8(&regs[rD], &regs[FL]); break;
        case 0x16: ld_8(&regs[rD], fetch8(ram, pc)); break;
        case 0x17: lrot(&regs[rA], 1, &regs[FL]); break;
        case 0x18: jr((int8_t)fetch8(ram, pc), pc, &regs[FL], -1); break;
        case 0x19: add_16(&regs[rH], &regs[rD], &regs[FL]); break;
        case 0x1a: ld_16(&regs[rA], *deref(ram, regs[rD], regs[rE])); break;
        case 0x1b: dec_16(&regs[rD]); break;
        case 0x1c: inc_8(&regs[rE], &regs[FL]); break;
        case 0x1d: dec_8(&regs[rE], &regs[FL]); break;
        case 0x1e: ld_8(&regs[rE], fetch8(ram, pc)); break;
        case 0x1f: rrot(&regs[rA], 1, &regs[FL]); break;
        /*-------------------------------------------------------*/
        case 0x20: jr((int8_t)fetch8(ram, pc), pc, &regs[FL], 0); break;
        case 0x21: ld_16(&regs[rH], fetch16(ram, pc)); break;
        case 0x22: ld_8(deref(ram, regs[rH], regs[rL]), regs[rA]); inc_16(&regs[rH]); break;
        case 0x23: inc_16(&regs[rH]); break;
        case 0x24: inc_8(&regs[rH], &regs[FL]); break;
        case 0x25: dec_8(&regs[rH], &regs[FL]); break;
        case 0x26: ld_8(&regs[rH], fetch8(ram, pc)); break;
        case 0x27: return -1; /* not implemented */
        case 0x28: jr((int8_t)fetch8(ram, pc), pc, &regs[FL], 1); break;
        case 0x29: add_16(&regs[rH], &regs[rH], &regs[FL]); break;
        case 0x2a: ld_8(&regs[rA], *deref(ram, regs[rH], regs[rL])); inc_16(&regs[rH]); break;
        case 0x2b: dec_16(&regs[rH]); break;
        case 0x2c: inc_8(&regs[rL], &regs[FL]); break;
        case 0x2d: dec_8(&regs[rL], &regs[FL]); break;
        case 0x2e: ld_8(&regs[rL], fetch8(ram, pc)); break;
        case 0x2f: cpl(&regs[rA], &regs[FL]); break;
        /*-------------------------------------------------------*/
        case 0x30: jr((int8_t)fetch8(ram, pc), pc, &regs[FL], 2); break;
        case 0x31: ld_sp(sp, fetch16(ram, pc)); break;
        case 0x32: ld_8(deref(ram, regs[rH], regs[rL]), regs[rA]); dec_16(&regs[rH]); break;
        case 0x33: *sp = *sp + 1; break;
        case 0x34: inc_8(deref(ram, regs[rH], regs[rL]), &regs[FL]); break;
        case 0x35: dec_8(deref(ram, regs[rH], regs[rL]), &regs[FL]); break;
        case 0x36: ld_8(deref(ram, regs[rH], regs[rL]), fetch8(ram, pc)); break;
        case 0x37: scf(&regs[FL]); break;
        case 0x38: jr((int8_t)fetch8(ram, pc), pc, &regs[FL], 3); break;
        case 0x39: add_sp_to(&regs[rH], *sp, &regs[FL]); break;
        case 0x3a: ld_8(&regs[rA], *deref(ram, regs[rH], regs[rL])); dec_16(&regs[rH]); break;
        case 0x3b: *sp = *sp - 1; break;
        case 0x3c: inc_8(&regs[rA], &regs[FL]); break;
        case 0x3d: dec_8(&regs[rA], &regs[FL]); break;
        case 0x3e: ld_8(&regs[rA], fetch8(ram, pc)); break;
        case 0x3f: ccf(&regs[FL]); break;
        /*-------------------------------------------------------*/
        case 0x40: ld_8(&regs[rB], regs[rB]); break;
        case 0x41: ld_8(&regs[rB], regs[rC]); break;
        case 0x42: ld_8(&regs[rB], regs[rD]); break;
        case 0x43: ld_8(&regs[rB], regs[rE]); break;
        case 0x44: ld_8(&regs[rB], regs[rH]); break;
        case 0x45: ld_8(&regs[rB], regs[rL]); break;
        case 0x46: ld_8(&regs[rB], *deref(ram, regs[rH], regs[rL])); break;
        case 0x47: ld_8(&regs[rB], regs[rA]); break;
        case 0x48: ld_8(&regs[rC], regs[rB]); break;
        case 0x49: ld_8(&regs[rC], regs[rC]); break;
        case 0x4a: ld_8(&regs[rC], regs[rD]); break;
        case 0x4b: ld_8(&regs[rC], regs[rE]); break;
        case 0x4c: ld_8(&regs[rC], regs[rH]); break;
        case 0x4d: ld_8(&regs[rC], regs[rL]); break;
        case 0x4e: ld_8(&regs[rC], *deref(ram, regs[rH], regs[rL])); break;
        case 0x4f: ld_8(&regs[rC], regs[rA]); break;
        /*-------------------------------------------------------*/
        case 0x50: ld_8(&regs[rD], regs[rB]); break;
        case 0x51: ld_8(&regs[rD], regs[rC]); break;
        case 0x52: ld_8(&regs[rD], regs[rD]); break;
        case 0x53: ld_8(&regs[rD], regs[rE]); break;
        case 0x54: ld_8(&regs[rD], regs[rH]); break;
        case 0x55: ld_8(&regs[rD], regs[rL]); break;
        case 0x56: ld_8(&regs[rD], *deref(ram, regs[rH], regs[rL])); break;
        case 0x57: ld_8(&regs[rD], regs[rA]); break;
        case 0x58: ld_8(&regs[rE], regs[rB]); break;
        case 0x59: ld_8(&regs[rE], regs[rC]); break;
        case 0x5a: ld_8(&regs[rE], regs[rD]); break;
        case 0x5b: ld_8(&regs[rE], regs[rE]); break;
        case 0x5c: ld_8(&regs[rE], regs[rH]); break;
        case 0x5d: ld_8(&regs[rE], regs[rL]); break;
        case 0x5e: ld_8(&regs[rE], *deref(ram, regs[rH], regs[rL])); break;
        case 0x5f: ld_8(&regs[rE], regs[rA]); break;
        /*-------------------------------------------------------*/
        case 0x60: ld_8(&regs[rH], regs[rB]); break;
        case 0x61: ld_8(&regs[rH], regs[rC]); break;
        case 0x62: ld_8(&regs[rH], regs[rD]); break;
        case 0x63: ld_8(&regs[rH], regs[rE]); break;
        case 0x64: ld_8(&regs[rH], regs[rH]); break;
        case 0x65: ld_8(&regs[rH], regs[rL]); break;
        case 0x66: ld_8(&regs[rH], *deref(ram, regs[rH], regs[rL])); break;
        case 0x67: ld_8(&regs[rH], regs[rA]); break;
        case 0x68: ld_8(&regs[rL], regs[rB]); break;
        case 0x69: ld_8(&regs[rL], regs[rC]); break;
        case 0x6a: ld_8(&regs[rL], regs[rD]); break;
        case 0x6b: ld_8(&regs[rL], regs[rE]); break;
        case 0x6c: ld_8(&regs[rL], regs[rH]); break;
        case 0x6d: ld_8(&regs[rL], regs[rL]); break;
        case 0x6e: ld_8(&regs[rL], *deref(ram, regs[rH], regs[rL])); break;
        case 0x6f: ld_8(&regs[rL], regs[rA]); break;
        /*-------------------------------------------------------*/
        case 0x70: ld_8(deref(ram, regs[rH], regs[rL]), regs[rB]); break;
        case 0x71: ld_8(deref(ram, regs[rH], regs[rL]), regs[rC]); break;
        case 0x72: ld_8(deref(ram, regs[rH], regs[rL]), regs[rD]); break;
        case 0x73: ld_8(deref(ram, regs[rH], regs[rL]), regs[rE]); break;
        case 0x74: ld_8(deref(ram, regs[rH], regs[rL]), regs[rH]); break;
        case 0x75: ld_8(deref(ram, regs[rH], regs[rL]), regs[rL]); break;
        case 0x76: return -1; /* not implemented */
        case 0x77: ld_8(deref(ram, regs[rH], regs[rL]), regs[rA]); break;
        case 0x78: ld_8(&regs[rA], regs[rB]); break;
        case 0x79: ld_8(&regs[rA], regs[rC]); break;
        case 0x7a: ld_8(&regs[rA], regs[rD]); break;
        case 0x7b: ld_8(&regs[rA], regs[rE]); break;
        case 0x7c: ld_8(&regs[rA], regs[rH]); break;
        case 0x7d: ld_8(&regs[rA], regs[rL]); break;
        case 0x7e: ld_8(&regs[rA], *deref(ram, regs[rH], regs[rL])); break;
        case 0x7f: ld_8(&regs[rA], regs[rA]); break;
        /*-------------------------------------------------------*/
        case 0x80: add_8(&regs[rA], regs[rB], 0, &regs[FL]); break;
        case 0x81: add_8(&regs[rA], regs[rC], 0, &regs[FL]); break;
        case 0x82: add_8(&regs[rA], regs[rD], 0, &regs[FL]); break;
        case 0x83: add_8(&regs[rA], regs[rE], 0, &regs[FL]); break;
        case 0x84: add_8(&regs[rA], regs[rH], 0, &regs[FL]); break;
        case 0x85: add_8(&regs[rA], regs[rL], 0, &regs[FL]); break;
        case 0x86: add_8(&regs[rA], *deref(ram, regs[rH], regs[rL]), 0, &regs[FL]); break;
        case 0x87: add_8(&regs[rA], regs[rA], 0, &regs[FL]); break;
        case 0x88: add_8(&regs[rA], regs[rB], 1, &regs[FL]); break;
        case 0x89: add_8(&regs[rA], regs[rC], 1, &regs[FL]); break;
        case 0x8a: add_8(&regs[rA], regs[rD], 1, &regs[FL]); break;
        case 0x8b: add_8(&regs[rA], regs[rE], 1, &regs[FL]); break;
        case 0x8c: add_8(&regs[rA], regs[rH], 1, &regs[FL]); break;
        case 0x8d: add_8(&regs[rA], regs[rL], 1, &regs[FL]); break;
        case 0x8e: add_8(&regs[rA], *deref(ram, regs[rH], regs[rL]), 1, &regs[FL]); break;
        case 0x8f: add_8(&regs[rA], regs[rA], 1, &regs[FL]); break;
        /*-------------------------------------------------------*/
        case 0x90: sub_8(&regs[rA], regs[rB], 0, &regs[FL]); break;
        case 0x91: sub_8(&regs[rA], regs[rC], 0, &regs[FL]); break;
        case 0x92: sub_8(&regs[rA], regs[rD], 0, &regs[FL]); break;
        case 0x93: sub_8(&regs[rA], regs[rE], 0, &regs[FL]); break;
        case 0x94: sub_8(&regs[rA], regs[rH], 0, &regs[FL]); break;
        case 0x95: sub_8(&regs[rA], regs[rL], 0, &regs[FL]); break;
        case 0x96: sub_8(&regs[rA], *deref(ram, regs[rH], regs[rL]), 0, &regs[FL]); break;
        case 0x97: sub_8(&regs[rA], regs[rA], 0, &regs[FL]); break;
        case 0x98: sub_8(&regs[rA], regs[rB], 1, &regs[FL]); break;
        case 0x99: sub_8(&regs[rA], regs[rC], 1, &regs[FL]); break;
        case 0x9a: sub_8(&regs[rA], regs[rD], 1, &regs[FL]); break;
        case 0x9b: sub_8(&regs[rA], regs[rE], 1, &regs[FL]); break;
        case 0x9c: sub_8(&regs[rA], regs[rH], 1, &regs[FL]); break;
        case 0x9d: sub_8(&regs[rA], regs[rL], 1, &regs[FL]); break;
        case 0x9e: sub_8(&regs[rA], *deref(ram, regs[rH], regs[rL]), 1, &regs[FL]); break;
        case 0x9f: sub_8(&regs[rA], regs[rA], 1, &regs[FL]); break;
        /*-------------------------------------------------------*/
        case 0xa0: land(&regs[rA], regs[rB], &regs[FL]); break;
        case 0xa1: land(&regs[rA], regs[rC], &regs[FL]); break;
        case 0xa2: land(&regs[rA], regs[rD], &regs[FL]); break;
        case 0xa3: land(&regs[rA], regs[rE], &regs[FL]); break;
        case 0xa4: land(&regs[rA], regs[rH], &regs[FL]); break;
        case 0xa5: land(&regs[rA], regs[rL], &regs[FL]); break;
        case 0xa6: land(&regs[rA], *deref(ram, regs[rH], regs[rL]), &regs[FL]); break;
        case 0xa7: land(&regs[rA], regs[rA], &regs[FL]); break;
        case 0xa8: lxor(&regs[rA], regs[rB], &regs[FL]); break;
        case 0xa9: lxor(&regs[rA], regs[rC], &regs[FL]); break;
        case 0xaa: lxor(&regs[rA], regs[rD], &regs[FL]); break;
        case 0xab: lxor(&regs[rA], regs[rE], &regs[FL]); break;
        case 0xac: lxor(&regs[rA], regs[rH], &regs[FL]); break;
        case 0xad: lxor(&regs[rA], regs[rL], &regs[FL]); break;
        case 0xae: lxor(&regs[rA], *deref(ram, regs[rH],regs[rL]), &regs[FL]); break;
        case 0xaf: lxor(&regs[rA], regs[rA], &regs[FL]); break;
        /*-------------------------------------------------------*/
        case 0xb0: lor(&regs[rA], regs[rB], &regs[FL]); break;
        case 0xb1: lor(&regs[rA], regs[rC], &regs[FL]); break;
        case 0xb2: lor(&regs[rA], regs[rD], &regs[FL]); break;
        case 0xb3: lor(&regs[rA], regs[rE], &regs[FL]); break;
        case 0xb4: lor(&regs[rA], regs[rH], &regs[FL]); break;
        case 0xb5: lor(&regs[rA], regs[rL], &regs[FL]); break;
        case 0xb6: lor(&regs[rA], *deref(ram, regs[rH], regs[rL]), &regs[FL]); break;
        case 0xb7: lor(&regs[rA], regs[rA], &regs[FL]); break;
        case 0xb8: lcp(regs[rA], regs[rB], &regs[FL]); break;
        case 0xb9: lcp(regs[rA], regs[rC], &regs[FL]); break;
        case 0xba: lcp(regs[rA], regs[rD], &regs[FL]); break;
        case 0xbb: lcp(regs[rA], regs[rE], &regs[FL]); break;
        case 0xbc: lcp(regs[rA], regs[rH], &regs[FL]); break;
        case 0xbd: lcp(regs[rA], regs[rL], &regs[FL]); break;
        case 0xbe: lcp(regs[rA], *deref(ram, regs[rH], regs[rL]), &regs[FL]); break;
        case 0xbf: lcp(regs[rA], regs[rA], &regs[FL]); break;
        /*-------------------------------------------------------*/
        case 0xc0: ret(pc, sp, ram, &regs[FL], 0); break;
        case 0xc1: pop(&regs[rB], sp, ram); break;
        case 0xc2: jp(fetch16(ram, pc), pc, &regs[FL], 0); break;
        case 0xc3: jp(fetch16(ram, pc), pc, &regs[FL], -1); break;
        case 0xc4: call(fetch16(ram, pc), pc, sp, ram, &regs[FL], 0); break;
        case 0xc5: push(&regs[rB], sp, ram); break;
        case 0xc6: add_8(&regs[rA], fetch8(ram, pc), 0, &regs[FL]); break;
        case 0xc7: rst(pc, sp, ram, 0); break;
        case 0xc8: ret(pc, sp, ram, &regs[FL], 1); break;
        case 0xc9: ret(pc, sp, ram, &regs[FL], -1); break;
        case 0xca: jp(fetch16(ram, pc), pc, &regs[FL], 1); break;
        case 0xcb: return exec_cb(fetch8(ram, pc), regs, ram, sp, pc);
        case 0xcc: call(fetch16(ram, pc), pc, sp, ram, &regs[FL], 1); break;
        case 0xcd: call(fetch16(ram, pc), pc, sp, ram, &regs[FL], -11); break;
        case 0xce: add_8(&regs[rA], fetch8(ram, pc), 1, &regs[FL]); break;
        case 0xcf: rst(pc, sp, ram, 1); break;
        /*-------------------------------------------------------*/
        case 0xd0: ret(pc, sp, ram, &regs[FL], 2); break;
        case 0xd1: pop(&regs[rD], sp, ram); break;
        case 0xd2: jp(fetch16(ram, pc), pc, &regs[FL], 2); break;
        case 0xd3: return -1; /* invalid opcode */
        case 0xd4: call(fetch16(ram, pc), pc, sp, ram, &regs[FL], 2); break;
        case 0xd5: push(&regs[rD], sp, ram); break;
        case 0xd6: sub_8(&regs[rA], fetch8(ram, pc), 0, &regs[FL]); break;
        case 0xd7: rst(pc, sp, ram, 2); break;
        case 0xd8: ret(pc, sp, ram, &regs[FL], 3); break;
        case 0xd9: ret(pc, sp, ram, &regs[FL], -1); break;
        case 0xda: jp(fetch16(ram, pc), pc, &regs[FL], 3); break;
        case 0xdb: return -1; /* invalid opcode */
        case 0xdc: call(fetch16(ram, pc), pc, sp, ram, &regs[FL], 3); break;
        case 0xdd: return -1; /* invalid opcode */
        case 0xde: sub_8(&regs[rA], fetch8(ram, pc), 1, &regs[FL]); break;
        case 0xdf: rst(pc, sp, ram, 3); break;
        /*-------------------------------------------------------*/
        case 0xe0: ld_8(deref(ram, 0xff, fetch8(ram, pc)), regs[rA]); break;
        case 0xe1: pop(&regs[rH], sp, ram); break;
        case 0xe2: ld_8(deref(ram, 0xff, regs[rC]), regs[rA]); break;
        case 0xe3: return -1; /* invalid opcode */
        case 0xe4: return -1; /* invalid opcode */
        case 0xe5: push(&regs[rH], sp, ram); break;
        case 0xe6: land(&regs[rA], fetch8(ram, pc), &regs[FL]); break;
        case 0xe7: rst(pc, sp, ram, 4); break;
        case 0xe8: add_to_sp(sp, fetch8(ram, pc), &regs[FL]); break;
        case 0xe9: jp((uint16_t)((regs[rH]<<8)+regs[rL]), pc, &regs[FL], -1); break;
        case 0xea: tmp_val=fetch16(ram, pc); ld_8(deref(ram, tmp_val>>8, (uint8_t)tmp_val), regs[rA]); break;
        case 0xeb: return -1; /* invalid opcode */
        case 0xec: return -1; /* invalid opcode */
        case 0xed: return -1; /* invalid opcode */
        case 0xee: lxor(&regs[rA], fetch8(ram, pc), &regs[FL]); break;
        case 0xef: rst(pc, sp, ram, 5); break;
        /*-------------------------------------------------------*/
        case 0xf0: ld_8(&regs[rA], *deref(ram, 0xff, fetch8(ram, pc))); break;
        case 0xf1: pop(&regs[rA], sp, ram); break;
        case 0xf2: ld_8(&regs[rA], *deref(ram, 0xff, regs[rC])); break;
        case 0xf3: return -1; /* not implemented */
        case 0xf4: return -1; /* invalid opcode */
        case 0xf5: push(&regs[rA], sp, ram); break;
        case 0xf6: lor(&regs[rA], fetch8(ram, pc), &regs[FL]); break;
        case 0xf7: rst(pc, sp, ram, 6); break;
        case 0xf8: add_to_sp(sp, fetch8(ram, pc), &regs[FL]); add_sp_to(&regs[rH], *sp, &regs[FL]); break;
        case 0xf9: ld_sp(sp, (uint16_t)((regs[rH]<<8)+regs[rL])); break;
        case 0xfa: tmp_val=fetch16(ram, pc); ld_8(&regs[rA], *deref(ram, tmp_val>>8, (uint8_t)tmp_val)); break;
        case 0xfb: return -1; /* not implemented */
        case 0xfc: return -1; /* invalid opcode */
        case 0xfd: return -1; /* invalid opcode */
        case 0xfe: lcp(regs[rA], fetch8(ram, pc), &regs[FL]); break;
        case 0xff: rst(pc, sp, ram, 7);
        default: return -1; /* invalid opcode */
	}
        return 0;
}

int exec_cb(uint8_t opcode, uint8_t* regs, uint8_t* ram, uint16_t* sp, uint16_t* pc) {
        switch (opcode)
        {
        case 0: rlc(&regs[rB], 0, &regs[FL]); break;
        case 0x01: rlc(&regs[rC], 0, &regs[FL]); break;
        case 0x02: rlc(&regs[rD], 0, &regs[FL]); break;
        case 0x03: rlc(&regs[rE], 0, &regs[FL]); break;
        case 0x04: rlc(&regs[rH], 0, &regs[FL]); break;
        case 0x05: rlc(&regs[rL], 0, &regs[FL]); break;
        case 0x06: rlc(deref(ram, regs[rH], regs[rL]), 0, &regs[FL]); break;
        case 0x07: rlc(&regs[rA], 0, &regs[FL]); break;
        case 0x08: rrc(&regs[rB], 0, &regs[FL]); break;
        case 0x09: rrc(&regs[rB], 0, &regs[FL]); break;
        case 0x0a: rrc(&regs[rD], 0, &regs[FL]); break;
        case 0x0b: rrc(&regs[rE], 0, &regs[FL]); break;
        case 0x0c: rrc(&regs[rH], 0, &regs[FL]); break;
        case 0x0d: rrc(&regs[rL], 0, &regs[FL]); break;
        case 0x0e: rrc(deref(ram, regs[rH], regs[rL]), 0, &regs[FL]); break;
        case 0x0f: rrc(&regs[rA], 0, &regs[FL]); break;
        /*-------------------------------------------------------*/
        case 0x10: lrot(&regs[rB], 0, &regs[FL]); break;
        case 0x11: lrot(&regs[rC], 0, &regs[FL]); break;
        case 0x12: lrot(&regs[rD], 0, &regs[FL]); break;
        case 0x13: lrot(&regs[rE], 0, &regs[FL]); break;
        case 0x14: lrot(&regs[rH], 0, &regs[FL]); break;
        case 0x15: lrot(&regs[rL], 0, &regs[FL]); break;
        case 0x16: lrot(deref(ram, regs[rH], regs[rL]), 0, &regs[FL]); break;
        case 0x17: lrot(&regs[rA], 0, &regs[FL]); break;
        case 0x18: rrot(&regs[rB], 0, &regs[FL]); break;
        case 0x19: rrot(&regs[rB], 0, &regs[FL]); break;
        case 0x1a: rrot(&regs[rD], 0, &regs[FL]); break;
        case 0x1b: rrot(&regs[rE], 0, &regs[FL]); break;
        case 0x1c: rrot(&regs[rH], 0, &regs[FL]); break;
        case 0x1d: rrot(&regs[rL], 0, &regs[FL]); break;
        case 0x1e: rrot(deref(ram, regs[rH], regs[rL]), 0, &regs[FL]); break;
        case 0x1f: rrot(&regs[rA], 0, &regs[FL]); break;
        /*-------------------------------------------------------*/
        case 0x20: sla(&regs[rB], &regs[FL]); break;
        case 0x21: sla(&regs[rC], &regs[FL]); break;
        case 0x22: sla(&regs[rD], &regs[FL]); break;
        case 0x23: sla(&regs[rE], &regs[FL]); break;
        case 0x24: sla(&regs[rH], &regs[FL]); break;
        case 0x25: sla(&regs[rL], &regs[FL]); break;
        case 0x26: sla(deref(ram, regs[rH], regs[rL]), &regs[FL]); break;
        case 0x27: sla(&regs[rA], &regs[FL]); break;
        case 0x28: sra(&regs[rB], &regs[FL]); break;
        case 0x29: sra(&regs[rC], &regs[FL]); break;
        case 0x2a: sra(&regs[rD], &regs[FL]); break;
        case 0x2b: sra(&regs[rE], &regs[FL]); break;
        case 0x2c: sra(&regs[rH], &regs[FL]); break;
        case 0x2d: sra(&regs[rL], &regs[FL]); break;
        case 0x2e: sra(deref(ram, regs[rH], regs[rL]), &regs[FL]); break;
        case 0x2f: sra(&regs[rA], &regs[FL]); break;
        /*-------------------------------------------------------*/
        case 0x30: swap(&regs[rB], &regs[FL]); break;
        case 0x31: swap(&regs[rC], &regs[FL]); break;
        case 0x32: swap(&regs[rD], &regs[FL]); break;
        case 0x33: swap(&regs[rE], &regs[FL]); break;
        case 0x34: swap(&regs[rH], &regs[FL]); break;
        case 0x35: swap(&regs[rL], &regs[FL]); break;
        case 0x36: swap(deref(ram, regs[rH], regs[rL]), &regs[FL]); break;
        case 0x37: swap(&regs[rA], &regs[FL]); break;
        case 0x38: srl(&regs[rB], &regs[FL]); break;
        case 0x39: srl(&regs[rC], &regs[FL]); break;
        case 0x3a: srl(&regs[rD], &regs[FL]); break;
        case 0x3b: srl(&regs[rE], &regs[FL]); break;
        case 0x3c: srl(&regs[rH], &regs[FL]); break;
        case 0x3d: srl(&regs[rL], &regs[FL]); break;
        case 0x3e: srl(deref(ram, regs[rH], regs[rL]), &regs[FL]); break;
        case 0x3f: srl(&regs[rA], &regs[FL]); break;
        /*-------------------------------------------------------*/
        case 0x40: bit(&regs[rB], 0, &regs[FL]); break;
        case 0x41: bit(&regs[rC], 0, &regs[FL]); break;
        case 0x42: bit(&regs[rD], 0, &regs[FL]); break;
        case 0x43: bit(&regs[rE], 0, &regs[FL]); break;
        case 0x44: bit(&regs[rH], 0, &regs[FL]); break;
        case 0x45: bit(&regs[rL], 0, &regs[FL]); break;
        case 0x46: bit(deref(ram, regs[rH], regs[rL]), 0, &regs[FL]); break;
        case 0x47: bit(&regs[rA], 0, &regs[FL]); break;
        case 0x48: bit(&regs[rB], 1, &regs[FL]); break;
        case 0x49: bit(&regs[rC], 1, &regs[FL]); break;
        case 0x4a: bit(&regs[rD], 1, &regs[FL]); break;
        case 0x4b: bit(&regs[rE], 1, &regs[FL]); break;
        case 0x4c: bit(&regs[rH], 1, &regs[FL]); break;
        case 0x4d: bit(&regs[rL], 1, &regs[FL]); break;
        case 0x4e: bit(deref(ram, regs[rH], regs[rL]), 1, &regs[FL]); break;
        case 0x4f: bit(&regs[rA], 1, &regs[FL]); break;
        /*-------------------------------------------------------*/
        case 0x50: bit(&regs[rB], 2, &regs[FL]); break;
        case 0x51: bit(&regs[rC], 2, &regs[FL]); break;
        case 0x52: bit(&regs[rD], 2, &regs[FL]); break;
        case 0x53: bit(&regs[rE], 2, &regs[FL]); break;
        case 0x54: bit(&regs[rH], 2, &regs[FL]); break;
        case 0x55: bit(&regs[rL], 2, &regs[FL]); break;
        case 0x56: bit(deref(ram, regs[rH], regs[rL]), 2, &regs[FL]); break;
        case 0x57: bit(&regs[rA], 2, &regs[FL]); break;
        case 0x58: bit(&regs[rB], 3, &regs[FL]); break;
        case 0x59: bit(&regs[rC], 3, &regs[FL]); break;
        case 0x5a: bit(&regs[rD], 3, &regs[FL]); break;
        case 0x5b: bit(&regs[rE], 3, &regs[FL]); break;
        case 0x5c: bit(&regs[rH], 3, &regs[FL]); break;
        case 0x5d: bit(&regs[rL], 3, &regs[FL]); break;
        case 0x5e: bit(deref(ram, regs[rH], regs[rL]), 3, &regs[FL]); break;
        case 0x5f: bit(&regs[rA], 3, &regs[FL]); break;
        /*-------------------------------------------------------*/
        case 0x60: bit(&regs[rB], 4, &regs[FL]); break;
        case 0x61: bit(&regs[rC], 4, &regs[FL]); break;
        case 0x62: bit(&regs[rD], 4, &regs[FL]); break;
        case 0x63: bit(&regs[rE], 4, &regs[FL]); break;
        case 0x64: bit(&regs[rH], 4, &regs[FL]); break;
        case 0x65: bit(&regs[rL], 4, &regs[FL]); break;
        case 0x66: bit(deref(ram, regs[rH], regs[rL]), 4, &regs[FL]); break;
        case 0x67: bit(&regs[rA], 4, &regs[FL]); break;
        case 0x68: bit(&regs[rB], 5, &regs[FL]); break;
        case 0x69: bit(&regs[rC], 5, &regs[FL]); break;
        case 0x6a: bit(&regs[rD], 5, &regs[FL]); break;
        case 0x6b: bit(&regs[rE], 5, &regs[FL]); break;
        case 0x6c: bit(&regs[rH], 5, &regs[FL]); break;
        case 0x6d: bit(&regs[rL], 5, &regs[FL]); break;
        case 0x6e: bit(deref(ram, regs[rH], regs[rL]), 5, &regs[FL]); break;
        case 0x6f: bit(&regs[rA], 5, &regs[FL]); break;
        /*-------------------------------------------------------*/
        case 0x70: bit(&regs[rB], 6, &regs[FL]); break;
        case 0x71: bit(&regs[rC], 6, &regs[FL]); break;
        case 0x72: bit(&regs[rD], 6, &regs[FL]); break;
        case 0x73: bit(&regs[rE], 6, &regs[FL]); break;
        case 0x74: bit(&regs[rH], 6, &regs[FL]); break;
        case 0x75: bit(&regs[rL], 6, &regs[FL]); break;
        case 0x76: bit(deref(ram, regs[rH], regs[rL]), 6, &regs[FL]); break;
        case 0x77: bit(&regs[rA], 6, &regs[FL]); break;
        case 0x78: bit(&regs[rB], 7, &regs[FL]); break;
        case 0x79: bit(&regs[rC], 7, &regs[FL]); break;
        case 0x7a: bit(&regs[rD], 7, &regs[FL]); break;
        case 0x7b: bit(&regs[rE], 7, &regs[FL]); break;
        case 0x7c: bit(&regs[rH], 7, &regs[FL]); break;
        case 0x7d: bit(&regs[rL], 7, &regs[FL]); break;
        case 0x7e: bit(deref(ram, regs[rH], regs[rL]), 7, &regs[FL]); break;
        case 0x7f: bit(&regs[rA], 7, &regs[FL]); break;
        /*-------------------------------------------------------*/
        case 0x80: resb(&regs[rB], 0); break;
        case 0x81: resb(&regs[rC], 0); break;
        case 0x82: resb(&regs[rD], 0); break;
        case 0x83: resb(&regs[rE], 0); break;
        case 0x84: resb(&regs[rH], 0); break;
        case 0x85: resb(&regs[rL], 0); break;
        case 0x86: resb(deref(ram, regs[rH], regs[rL]), 0); break;
        case 0x87: resb(&regs[rA], 0); break;
        case 0x88: resb(&regs[rB], 1); break;
        case 0x89: resb(&regs[rC], 1); break;
        case 0x8a: resb(&regs[rD], 1); break;
        case 0x8b: resb(&regs[rE], 1); break;
        case 0x8c: resb(&regs[rH], 1); break;
        case 0x8d: resb(&regs[rL], 1); break;
        case 0x8e: resb(deref(ram, regs[rH], regs[rL]), 1); break;
        case 0x8f: resb(&regs[rA], 1); break;
        /*-------------------------------------------------------*/
        case 0x90: resb(&regs[rB], 2); break;
        case 0x91: resb(&regs[rC], 2); break;
        case 0x92: resb(&regs[rD], 2); break;
        case 0x93: resb(&regs[rE], 2); break;
        case 0x94: resb(&regs[rH], 2); break;
        case 0x95: resb(&regs[rL], 2); break;
        case 0x96: resb(deref(ram, regs[rH], regs[rL]), 2); break;
        case 0x97: resb(&regs[rA], 2); break;
        case 0x98: resb(&regs[rB], 3); break;
        case 0x99: resb(&regs[rC], 3); break;
        case 0x9a: resb(&regs[rD], 3); break;
        case 0x9b: resb(&regs[rE], 3); break;
        case 0x9c: resb(&regs[rH], 3); break;
        case 0x9d: resb(&regs[rL], 3); break;
        case 0x9e: resb(deref(ram, regs[rH], regs[rL]), 3); break;
        case 0x9f: resb(&regs[rA], 3); break;
        /*-------------------------------------------------------*/
        case 0xa0: resb(&regs[rB], 4); break;
        case 0xa1: resb(&regs[rC], 4); break;
        case 0xa2: resb(&regs[rD], 4); break;
        case 0xa3: resb(&regs[rE], 4); break;
        case 0xa4: resb(&regs[rH], 4); break;
        case 0xa5: resb(&regs[rL], 4); break;
        case 0xa6: resb(deref(ram, regs[rH], regs[rL]), 4); break;
        case 0xa7: resb(&regs[rA], 4); break;
        case 0xa8: resb(&regs[rB], 5); break;
        case 0xa9: resb(&regs[rC], 5); break;
        case 0xaa: resb(&regs[rD], 5); break;
        case 0xab: resb(&regs[rE], 5); break;
        case 0xac: resb(&regs[rH], 5); break;
        case 0xad: resb(&regs[rL], 5); break;
        case 0xae: resb(deref(ram, regs[rH], regs[rL]), 5); break;
        case 0xaf: resb(&regs[rA], 5); break;
        /*-------------------------------------------------------*/
        case 0xb0: resb(&regs[rB], 6); break;
        case 0xb1: resb(&regs[rC], 6); break;
        case 0xb2: resb(&regs[rD], 6); break;
        case 0xb3: resb(&regs[rE], 6); break;
        case 0xb4: resb(&regs[rH], 6); break;
        case 0xb5: resb(&regs[rL], 6); break;
        case 0xb6: resb(deref(ram, regs[rH], regs[rL]), 6); break;
        case 0xb7: resb(&regs[rA], 6); break;
        case 0xb8: resb(&regs[rB], 7); break;
        case 0xb9: resb(&regs[rC], 7); break;
        case 0xba: resb(&regs[rD], 7); break;
        case 0xbb: resb(&regs[rE], 7); break;
        case 0xbc: resb(&regs[rH], 7); break;
        case 0xbd: resb(&regs[rL], 7); break;
        case 0xbe: resb(deref(ram, regs[rH], regs[rL]), 7); break;
        case 0xbf: resb(&regs[rA], 7); break;
        /*-------------------------------------------------------*/
        case 0xc0: setb(&regs[rB], 0); break;
        case 0xc1: setb(&regs[rC], 0); break;
        case 0xc2: setb(&regs[rD], 0); break;
        case 0xc3: setb(&regs[rE], 0); break;
        case 0xc4: setb(&regs[rH], 0); break;
        case 0xc5: setb(&regs[rL], 0); break;
        case 0xc6: setb(deref(ram, regs[rH], regs[rL]), 0); break;
        case 0xc7: setb(&regs[rA], 0); break;
        case 0xc8: setb(&regs[rB], 1); break;
        case 0xc9: setb(&regs[rC], 1); break;
        case 0xca: setb(&regs[rD], 1); break;
        case 0xcb: setb(&regs[rE], 1); break;
        case 0xcc: setb(&regs[rH], 1); break;
        case 0xcd: setb(&regs[rL], 1); break;
        case 0xce: setb(deref(ram, regs[rH], regs[rL]), 1); break;
        case 0xcf: setb(&regs[rA], 1); break;
        /*-------------------------------------------------------*/
        case 0xd0: setb(&regs[rB], 2); break;
        case 0xd1: setb(&regs[rC], 2); break;
        case 0xd2: setb(&regs[rD], 2); break;
        case 0xd3: setb(&regs[rE], 2); break;
        case 0xd4: setb(&regs[rH], 2); break;
        case 0xd5: setb(&regs[rL], 2); break;
        case 0xd6: setb(deref(ram, regs[rH], regs[rL]), 2); break;
        case 0xd7: setb(&regs[rA], 2); break;
        case 0xd8: setb(&regs[rB], 3); break;
        case 0xd9: setb(&regs[rC], 3); break;
        case 0xda: setb(&regs[rD], 3); break;
        case 0xdb: setb(&regs[rE], 3); break;
        case 0xdc: setb(&regs[rH], 3); break;
        case 0xdd: setb(&regs[rL], 3); break;
        case 0xde: setb(deref(ram, regs[rH], regs[rL]), 3); break;
        case 0xdf: setb(&regs[rA], 3); break;
        /*-------------------------------------------------------*/
        case 0xe0: setb(&regs[rB], 4); break;
        case 0xe1: setb(&regs[rC], 4); break;
        case 0xe2: setb(&regs[rD], 4); break;
        case 0xe3: setb(&regs[rE], 4); break;
        case 0xe4: setb(&regs[rH], 4); break;
        case 0xe5: setb(&regs[rL], 4); break;
        case 0xe6: setb(deref(ram, regs[rH], regs[rL]), 4); break;
        case 0xe7: setb(&regs[rA], 4); break;
        case 0xe8: setb(&regs[rB], 5); break;
        case 0xe9: setb(&regs[rC], 5); break;
        case 0xea: setb(&regs[rD], 5); break;
        case 0xeb: setb(&regs[rE], 5); break;
        case 0xec: setb(&regs[rH], 5); break;
        case 0xed: setb(&regs[rL], 5); break;
        case 0xee: setb(deref(ram, regs[rH], regs[rL]), 5); break;
        case 0xef: setb(&regs[rA], 5); break;
        /*-------------------------------------------------------*/
        case 0xf0: setb(&regs[rB], 6); break;
        case 0xf1: setb(&regs[rC], 6); break;
        case 0xf2: setb(&regs[rD], 6); break;
        case 0xf3: setb(&regs[rE], 6); break;
        case 0xf4: setb(&regs[rH], 6); break;
        case 0xf5: setb(&regs[rL], 6); break;
        case 0xf6: setb(deref(ram, regs[rH], regs[rL]), 6); break;
        case 0xf7: setb(&regs[rA], 6); break;
        case 0xf8: setb(&regs[rB], 7); break;
        case 0xf9: setb(&regs[rC], 7); break;
        case 0xfa: setb(&regs[rD], 7); break;
        case 0xfb: setb(&regs[rE], 7); break;
        case 0xfc: setb(&regs[rH], 7); break;
        case 0xfd: setb(&regs[rL], 7); break;
        case 0xfe: setb(deref(ram, regs[rH], regs[rL]), 7); break;
        case 0xff: setb(&regs[rA], 7); break;
        default: return -1; /* invalid opcode */
        }
        return 0;
}