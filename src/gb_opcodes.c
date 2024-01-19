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
	}
}