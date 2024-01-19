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
        case 0x30:
        case 0x31: ld_sp(sp, fetch16(ram, pc)); break;
	}
}