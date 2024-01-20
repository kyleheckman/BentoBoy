#include "gb_isa.h"
#include "gb_opcodes.h"

/* REGS:    0:A | 1:B | 2:C | 3:D | 4:E | 5:H | 6:L */
#define rA 0
#define rB 1
#define rC 2
#define rD 3
#define rE 4
#define rH 5
#define rL 6

int exec_instr(uint8_t opcode, uint8_t* regs, uint8_t* ram, uint8_t* flags, uint16_t* sp, uint16_t* pc) {
	switch (opcode)
	{
        case 0: break;	 /* NOP */
        case 0x01: ld_16(&regs[rB], fetch16(ram, pc)); break;
        case 0x02: ld_8(deref(ram, regs[rB], regs[rC]), regs[rA]); break;
        case 0x03: inc_16(&regs[rB]); break;
        case 0x04: inc_8(&regs[rB], flags); break;
        case 0x05: dec_8(&regs[rB], flags); break;
        case 0x06: ld_8(&regs[rB], fetch8(ram, pc)); break;
        case 0x07: rlca(); break;   /* not implemented */
        case 0x08: ld_16(deref(ram, fetch8(ram, pc), fetch8(ram, pc)), *sp); break;
        case 0x09: add_16(&regs[rH], &regs[rB], flags); break;
        case 0x0a: ld_8(&regs[rA], *deref(ram, regs[rB], regs[rC])); break;
        case 0x0b: dec_16(&regs[rB]); break;
        case 0x0c: inc_8(&regs[rC], flags); break;
        case 0x0d: dec_8(&regs[rC], flags); break;
        case 0x0e: ld_8(&regs[rC], fetch8(ram, pc)); break;
        case 0x0f: rrca(); break;   /* not implemented */
        /*-------------------------------------------------------*/
        case 0x10: break;   /* STOP, not implemented */
        case 0x11: ld_16(&regs[rD], fetch16(ram, pc)); break;
        case 0x12: ld_8(deref(ram, regs[rD], regs[rE]), regs[rA]); break;
        case 0x13: inc_16(&regs[rD]); break;
        case 0x14: inc_8(&regs[rD], flags); break;
        case 0x15: dec_8(&regs[rD], flags); break;
        case 0x16: ld_8(&regs[rD], fetch8(ram, pc)); break;
        case 0x17: break; /* not implemented */
        case 0x18: break; /* not implemented */
        case 0x19: add_16(&regs[rH], &regs[rD], flags); break;
        case 0x1a: ld_16(&regs[rA], *deref(ram, regs[rD], regs[rE])); break;
        case 0x1b: dec_16(&regs[rD]); break;
        case 0x1c: inc_8(&regs[rE], flags); break;
        case 0x1d: dec_8(&regs[rE], flags); break;
        case 0x1e: ld_8(&regs[rE], fetch8(ram, pc)); break;
        case 0x1f: /* not implemented */
        /*-------------------------------------------------------*/
        case 0x20: /* not implemented */
        case 0x21: ld_16(&regs[rH], fetch16(ram, pc)); break;
        case 0x22: ld_8(deref(ram, regs[rH], regs[rL]), regs[rA]); inc_16(&regs[rH]); break;
        case 0x23: inc_16(&regs[rH]); break;
        case 0x24: inc_8(&regs[rH], flags); break;
        case 0x25: dec_8(&regs[rH], flags); break;
        case 0x26: ld_8(&regs[rH], fetch8(ram, pc)); break;
        case 0x27: /* not implemented */
        case 0x28: /* not implemented */
        case 0x29: add_16(&regs[rH], &regs[rH], flags); break;
        case 0x2a: ld_8(&regs[rA], *deref(ram, regs[rH], regs[rL])); inc_16(&regs[rH]); break;
        case 0x2b: dec_16(&regs[rH]); break;
        case 0x2c: inc_8(&regs[rL], flags); break;
        case 0x2d: dec_8(&regs[rL], flags); break;
        case 0x2e: ld_8(&regs[rL], fetch8(ram, pc)); break;
        case 0x2f: /* not implemented */
        /*-------------------------------------------------------*/
        case 0x30: /* not implemened*/
        case 0x31: ld_sp(sp, fetch16(ram, pc)); break;
        case 0x32: ld_8(deref(ram, regs[rH], regs[rL]), regs[rA]); dec_16(&regs[rH]); break;
        case 0x33: *sp = *sp + 1; break;
        case 0x34: inc_8(deref(ram, regs[rH], reg[rL]), flags); break;
        case 0x35: dec_8(deref(ram, regs[rH], regs[rL]), flags); break;
        case 0x36: ld_8(deref(ram, regs[rH], regs[rL]), fetch8(ram, pc)); break;
        case 0x37: /* not implemented */
        case 0x38: /* not implemented */
        case 0x39: add_sp_to(&regs[rH], *sp); break;
        case 0x3a: ld_8(&regs[rA], *deref(ram, rgs[rH], regs[rL])); dec_16(&regs[rH]); break;
        case 0x3b: *sp = *sp - 1; break;
        case 0x3c: inc_8(&regs[rA], flags); break;
        case 0x3d: dec_8(&regs[rA], flags); break;
        case 0x3e: ld_8(&regs[rA], fetch8(ram, pc)); break;
        case 0x3f: /* not implemented */
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
        case 0x76: /* not implemented */
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
        case 0x80: add_8(&regs[rA], regs[rB], 0, flags); break;
        case 0x81: add_8(&regs[rA], regs[rC], 0, flags); break;
        case 0x82: add_8(&regs[rA], regs[rD], 0, flags); break;
        case 0x83: add_8(&regs[rA], regs[rE], 0, flags); break;
        case 0x84: add_8(&regs[rA], regs[rH], 0, flags); break;
        case 0x85: add_8(&regs[rA], regs[rL], 0, flags); break;
        case 0x86: add_8(&regs[rA], *deref(ram, regs[rH], regs[rL]), 0, flags); break;
        case 0x87: add_8(&regs[rA], regs[rA], 0, flags); break;
        case 0x88: add_8(&regs[rA], regs[rB], 1, flags); break;
        case 0x89: add_8(&regs[rA], regs[rC], 1, flags); break;
        case 0x8a: add_8(&regs[rA], regs[rD], 1, flags); break;
        case 0x8b: add_8(&regs[rA], regs[rE], 1, flags); break;
        case 0x8c: add_8(&regs[rA], regs[rH], 1, flags); break;
        case 0x8d: add_8(&regs[rA], regs[rL], 1, flags); break;
        case 0x8e: add_8(&regs[rA], *deref(ram, regs[rH], regs[rL]), 1, flags); break;
        case 0x8f: add_8(&regs[rA], regs[rA], 1, flags); break;
        /*-------------------------------------------------------*/
        case 0x90: sub_8(&regs[rA], regs[rB], 0, flags); break;
        case 0x91: sub_8(&regs[rA], regs[rC], 0, flags); break;
        case 0x92: sub_8(&regs[rA], regs[rD], 0, flags); break;
        case 0x93: sub_8(&regs[rA], regs[rE], 0, flags); break;
        case 0x94: sub_8(&regs[rA], regs[rH], 0, flags); break;
        case 0x95: sub_8(&regs[rA], regs[rL], 0, flags); break;
        case 0x96: sub_8(&regs[rA], *deref(ram, regs[rH], regs[rL]), 0, flags); break;
        case 0x97: sub_8(&regs[rA], regs[rA], 0, flags); break;
        case 0x98: sub_8(&regs[rA], regs[rB], 1, flags); break;
        case 0x99: sub_8(&regs[rA], regs[rC], 1, flags); break;
        case 0x9a: sub_8(&regs[rA], regs[rD], 1, flags); break;
        case 0x9b: sub_8(&regs[rA], regs[rE], 1, flags); break;
        case 0x9c: sub_8(&regs[rA], regs[rH], 1, flags); break;
        case 0x9d: sub_8(&regs[rA], regs[rL], 1, flags); break;
        case 0x9e: sub_8(&regs[rA], *deref(ram, regs[rH], regs[rL]), 1, flags); break;
        case 0x9f: sub_8(&regs[rA], regs[rA], 1, flags); break;
        /*-------------------------------------------------------*/
        case 0xa0: land(&regs[rA], regs[rB], flags); break;
        case 0xa1: land(&regs[rA], regs[rC], flags); break;
        case 0xa2: land(&regs[rA], regs[rD], flags); break;
        case 0xa3: land(&regs[rA], regs[rE], flags); break;
        case 0xa4: land(&regs[rA], regs[rH], flags); break;
        case 0xa5: land(&regs[rA], regs[rL], flags); break;
        case 0xa6: land(&regs[rA], *deref(ram, regs[rH], regs[rL]), flags); break;
        case 0xa7: land(&regs[rA], regs[rA], flags); break;
        case 0xa8: lxor(&regs[rA], regs[rB], flags); break;
        case 0xa9: lxor(&regs[rA], regs[rC], flags); break;
        case 0xaa: lxor(&regs[rA], regs[rD], flags); break;
        case 0xab: lxor(&regs[rA], regs[rE], flags); break;
        case 0xac: lxor(&regs[rA], regs[rH], flags); break;
        case 0xad: lxor(&regs[rA], regs[rL], flags); break;
        case 0xae: lxor(&regs[rA], *deref(ram, regs[rH],regs[rL]), flags); break;
        case 0xaf: lxor(&regs[rA], regs[rA], flags); break;
        /*-------------------------------------------------------*/
        case 0xb0: lor(&regs[rA], regs[rB], flags); break;
        case 0xb1: lor(&regs[rA], regs[rC], flags); break;
        case 0xb2: lor(&regs[rA], regs[rD], flags); break;
        case 0xb3: lor(&regs[rA], regs[rE], flags); break;
        case 0xb4: lor(&regs[rA], regs[rH], flags); break;
        case 0xb5: lor(&regs[rA], regs[rL], flags); break;
        case 0xb6: lor(&regs[rA], *deref(ram, regs[rH], regs[rL]), flags); break;
        case 0xb7: lor(&regs[rA], regs[rA], flags); break;
        case 0xb8: lcp(regs[rA], regs[rB], flags); break;
        case 0xb9: lcp(regs[rA], regs[rC], flags); break;
        case 0xba: lcp(regs[rA], regs[rD], flags); break;
        case 0xbb: lcp(regs[rA], regs[rE], flags); break;
        case 0xbc: lcp(regs[rA], regs[rH], flags); break;
        case 0xbd: lcp(regs[rA], regs[rL], flags); break;
        case 0xbe: lcp(regs[rA], *deref(ram, regs[rH], reg[rL]), flags); break;
        case 0xbf: lcp(regs[rA], regs[rA], flags); break;
        /*-------------------------------------------------------*/
        case 0xc0: /* not implemented */
        case 0xc1: pop(&regs[rB], sp, ram); break;
        case 0xc2: jp(fetch16(ram, pc), pc, flags, 0); break;
        case 0xc3: jp(fetch16(ram, pc), pc, flags, -1); break;
        case 0xc4: /* not implemented */
        case 0xc5: push(&regsd[rB], sp, ram); break;
        case 0xc6: add_8(&regs[rA], fetch8(ram, pc), 0, flags); break;
        case 0xc7: /* not implemented */
        case 0xc8: /* not imlpemented */
        case 0xc9: /* not implemented */
        case 0xca: jp(fetch16(ram, pc), pc, flags, 1); break;
        case 0xcb: exec_cb(fetch8(ram, pc), regs, ram, flags, sp, pc); break;
        case 0xcc: /* not implemented */
        case 0xcd: /* not implemented */
        case 0xce: add_8(&regs[rA], fetch8(ram, pc), 1, flags); break;
        case 0xcf: /* not implemented */
        /*-------------------------------------------------------*/

	}
}

int exec_cb(uint8_t opcode, uint8_t* regs, uint8_t* ram, uint8_t* flags, uint16_t* sp, uint16_t* pc) {

}