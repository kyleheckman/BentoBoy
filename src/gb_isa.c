#include "gb_isa.h"

/*--------------------------------------------------*/
/* loads dest into pc if flags meet cond */
/* default is cond not in option is no test condition */
void jp(uint16_t dest, uint16_t* pc, uint8_t* flags, int cond) {
	switch (cond) {
		case 0: if (!(*flags & 0x80)) {*pc = dest;} break;	/* NZ: Z == 0 */
		case 1: if (*flags & 0x80) {*pc = dest;} break;		/* Z == 1 */
		case 2: if (!(*flags & 0x10)) {*pc = dest;} break;	/* NC: CY == 0 */
		case 3: if (*flags & 0x10) {*pc = dest;} break;		/* CY == 1 */
		default: *pc = dest; break;
	}
}

/*--------------------------------------------------*/
/* short jump, increments PC by ofs*/
/* default is cond not in option is no test condition */
void jr(int8_t ofs, uint16_t* pc, uint8_t* flags, int cond) {
	switch (cond) {
		case 0: if (!(*flags & 0x80)) {*pc = *pc + ofs;} break;		/* NZ: Z == 0 */
		case 1: if (*flags & 0x80) {*pc = *pc + ofs;} break;		/* Z == 1 */
		case 2: if (!(*flags & 0x10)) {*pc = *pc + ofs;} break;		/* NC: CY == 0 */
		case 3: if (*flags & 0x10) {*pc = *pc + ofs;} break;		/* CY == 1 */
		default: *pc = *pc + ofs; break;
	}
}

/*--------------------------------------------------*/
/* calls function at location dest (sets PC to dest) */
/* default is cond not in option is no test condition */
void call(uint16_t dest, uint16_t* pc uint16_t* sp, uint8_t* ram, uint8_t* flags, int cond) {
	/* if conditonal is false return, otherwise load new PC */
	switch(cond) {
		case 0: if (*flags & 0x80) {return;} break;		/* NZ: Z == 0 - returns if Z == 1 */
		case 1: if (!(*flags & 0x80)) {return;} break;	/* Z == 1 - returns if Z == 0 */
		case 2: if (*flags & 0x10) {return;} break;		/* NC: C == 0 - returns if C == 1*/
		case 3: if (!(*flags & 0x10)) {return;} break;	/* C == 1 - returns if C == 0 */
		default:
	}
	
	/* store current PC on stack */
	*sp = *sp - 1;
	ram[*sp] = *pc >> 8;
	*sp = *sp - 1;
	ram[*sp] = (uint8_t)*pc;

	/* load address of called function to PC */
	*pc = dest;
}

/*--------------------------------------------------*/
/* returns operation to PC before call (PC stored on stack) */
void ret(uint16_t* pc, uint16_t* sp, uint8_t* ram, uint8_t* flags, int cond) {
	/* if conditonal is false return, otherwise load new PC */
	switch(cond) {
		case 0: if (*flags & 0x80) {return;} break;		/* NZ: Z == 0 - returns if Z == 1 */
		case 1: if (!(*flags & 0x80)) {return;} break;	/* Z == 1 - returns if Z == 0 */
		case 2: if (*flags & 0x10) {return;} break;		/* NC: C == 0 - returns if C == 1*/
		case 3: if (!(*flags & 0x10)) {return;} break;	/* C == 1 - returns if C == 0 */
		default:
	}
	
	/* reset PC */
	*pc = ram[*sp] + (ram[*(sp+1)] << 8);
	*sp = *sp + 2;
}

/*--------------------------------------------------*/
/* store current PC on stack and load page 0 location to PC, depending on value of cond */
void rst(uint16_t* pc, uint16_t *sp, uint8_t* ram, int cond) {
	uint16_t addr = 0;
	switch(cond) {
		case 1: addr = 0x8; break;
		case 2: addr = 0x10; break;
		case 3: addr = 0x18; break;
		case 4: addr = 0x20; break;
		case 5: addr = 0x28; break;
		case 6: addr = 0x30; break;
		case 7: addr = 0x38; break;
		default:
	}

	/* store PC to stack */
	*sp = *sp - 1;
	ram[*sp] = *pc >> 8;
	*sp = *sp - 1;
	ram[*sp] = (uint8_t)*pc;

	/* load new PC */
	*pc = addr;
}

/*--------------------------------------------------*/
/* copies the val from src into dest */
void ld_8(uint8_t* dest, uint8_t src) {
	*dest = src;
}

/*--------------------------------------------------*/
/* copies val into 2 bytes starting at location dest */
void ld_16(uint8_t* dest, uint16_t val) {
	*dest = (uint8_t)(val >> 8);
	*(dest+1) = (uint8_t)(val & 0xff);
}

/*--------------------------------------------------*/
/* copies 16-bit value to stack pointer*/
void ld_sp(uint16_t* sp, uint16_t val) {
    *sp = val;
}

/*--------------------------------------------------*/
/* push 16-bit value to stack */
/* inserts srcH @ sp-1, srcL @ sp-2*/
void push(uint8_t* src, uint16_t* sp, uint8_t* ram) {
	*sp = *sp - 1;
	ram[*sp] = *src;
	*sp = *sp - 1;
	ram[*sp] = *(src+1);
}

/*--------------------------------------------------*/
/* pop 16-bit value from stack, store at dest */
/* pops in order low byte then high byte*/
void pop(uint8_t* dest, uint16_t* sp, uint8_t* ram) {
	*(dest+1) = ram[*sp];
	*sp = *sp + 1;
	*dest = ram[*sp];
	*sp = *sp + 1;
}

/*--------------------------------------------------*/
/* increments 8-bit register dest by 1 */
void inc_8(uint8_t* dest, uint8_t* flags) {
	*dest = *dest + 1;
	
	/* set flags */
	*flags = (*flags & 0x70) | (!*dest << 7);								/* set Z flag */
	*flags = (*flags & 0xd0) | (((*dest ^ (*dest - 1) ^ 1) & 0x10) << 1);	/* set H flag */
	*flags = *flags & 0xb0; 												/* unset N flag */
}

/*--------------------------------------------------*/
/* increments 16-bit value at {dest, dest+1} */
void inc_16(uint8_t* dest) {
	uint16_t val = (uint16_t)((*dest << 8) + *(dest+1));
	val++;
	*dest = (uint8_t)(val >> 8);
	*(dest+1) = (uint8_t)(val & 0xff);
}

/*--------------------------------------------------*/
/* decrement 8-bit register dest by 1 */
void dec_8(uint8_t* dest, uint8_t* flags) {
	*dest = *dest - 1;

	/* set flags */
	*flags = (*flags & 0x70) | (!*dest << 7);							/* set Z flag */
	*flags = (*flags & 0xd0) | (((int)((*dest+1) & 0xf) - 1 < 0) << 5);	/* set H flag */
	*flags = *flags | 0x40;												/* set N flag */
}

/*--------------------------------------------------*/
/* decrement 16-bit register by 1 */
void dec_16(uint8_t* dest) {
	uint16_t val = (uint16_t)((*dest << 8) + *(dest+1));
	val--;
	*dest = (uint8_t)(val >> 8);
	*(dest+1) = (uint8_t)(val & 0xff);
}

/*--------------------------------------------------*/
/* add together dest & src (and CY if adc is set) and store results in dest */
void add_8(uint8_t* dest, uint8_t src, int adc, uint8_t* flags) {
    uint8_t cy = 0;
    if (adc) {
        cy = (*flags >> 4) & 0x1;
    }
    uint8_t old = *dest;
	*dest = *dest + src + cy;

	/* set flags */
	*flags = (*flags & 0x70) | (!*dest << 7);								/* set Z flag */
	*flags = *flags & 0xb0;													/* unset N flag */
	*flags = (*flags & 0xd0) | (((*dest ^ src ^ cy ^ old) & 0x10) << 1);	/* set H flag */
	*flags = (*flags & 0xe0) | (((int)(old + src + cy) > *dest) << 4);		/* set CY flag */
}

/*--------------------------------------------------*/
/* add 16-bit values src & dest, store in dest */
void add_16(uint8_t* dest, uint8_t* src, uint8_t* flags) {
	uint16_t d16 = (uint16_t)((*dest << 8) + *(dest+1));
	uint16_t s16 = (uint16_t)((*src << 8) + *(src+1));
	uint16_t val = d16 + s16;
	ld_16(dest, val);

	/* set flags */
	*flags = (*flags & 0xe0) | (((int)(d16 + s16) > val) << 4);		/* set CY flag */
	*flags = (*flags & 0xd0) | (((d16 ^ s16 ^ val) & 0x100) >> 3);	/* set H flag */
	*flags = *flags & 0xb0;											/* unset N flag */
}

/*--------------------------------------------------*/
/* add value of sp to 16-bit reg pair dest */
void add_sp_to(uint8_t* dest, uint16_t sp, uint8_t* flags) {
	uint16_t d16 = (uint16_t)((*dest << 8) + *(dest+1));
	uint16_t val = d16 + sp;
	ld_16(dest, val);

	/* set flags */
	*flags = (*flags & 0xe0) | (((int)(d16 + sp) > val) << 4);		/* set CY flag */
	*flags = (*flags & 0xd0) | (((d16 ^ sp ^ val) & 0x100) >> 3);	/* set H flag */
	*flags = *flags & 0xb0;											/* unset N flag */
}

/*--------------------------------------------------*/
/* add signed 8-bit value to sp */
void add_to_sp(uint16_t* sp, int8_t operand, uint8_t* flags) {
	uint16_t old = *sp;
	*sp = *sp + operand;

	/* set flags */
	*flags = 0;
	*flags = *flags | (((int)(operand + old) > *sp) << 4);		/* set CY flag */
	*flags = *flags | (((old ^ sp ^ operand) & 0x100) >> 3);	/* set H flag */
}

/*--------------------------------------------------*/
/* subtract values of src (and CY if sbc set) from dest, store result in dest */
void sub_8(uint8_t* dest, uint8_t src, int sbc, uint8_t* flags) {
	uint8_t cy = 0;
	if (sbc) {
		cy = (*flags >> 4) & 0x1; 
	}
	uint8_t old = *dest;
	*dest = *dest - src - cy;

	/* set flags */
	*flags = (*flags & 0x70) | (!*dest << 7);												/* set Z flag */
	*flags = *flags | 0x40;																	/* set N flag */
	*flags = (*flags & 0xd0) | (((uint8_t)((old & 0xf) - ((src + cy) & 0xf)) & 0x10) << 1);	/* set H flag */
	*flags = (*flags & 0xe0) | (((int)(old - src - cy) < 0) << 4);							/* set CY flag */
}

/*--------------------------------------------------*/
/* calculates the bitwise AND of dest & src, stores result in dest */
void land(uint8_t* dest, uint8_t src, uint8_t* flags) {
	*dest = *dest & src;

	/* set flags */
	*flags = 0x20 | (!*dest << 7);	/* set Z flag, H flag always set */
}

/*--------------------------------------------------*/
/* calculates the bitwise XOR of dest & src, stores result in dest */
void lxor(uint8_t* dest, uint8_t src, uint8_t* flags) {
	*dest = *dest ^ src;

	/* set flags */
	*flags = 0 | (!*dest << 7);		/* set Z flag */
}

/*--------------------------------------------------*/
/* calculates the bitwise OR of dest & src, stores result in dest */
void lor(uint8_t* dest, uint8_t src, uint8_t* flags) {
	*dest = *dest | src;

	/* set flags */
	*flags = 0 | (!*dest << 7);
}

/*--------------------------------------------------*/
/* compares dest & src */
/* set Z iff equal, set H if src < dest, set CY if src > dest*/
void lcp(uint8_t dest, uint8_t src, uint8_t* flags) {
	if (*dest == src) {*flags = 0xc0;}
	if (*dest < src) {*flags = 0x50;}
	if (*dest > src) {*flags = 0x60;}
}

/*--------------------------------------------------*/
/* rotates reg 1 bit left, stores reg[7] in CY, reg[7]->reg[0] */
void rlc(uint8_t* reg, int is_ra, uint8_t* flags) {
	uint8_t cy = *reg >> 7;
	*reg = (*reg << 1) | cy;
	
	/* set flags */
	*flags = 0 | (cy << 4);	/* set CY */
	*flags = is_ra == 1 ? *flags : *flags | ((!*reg) << 7);	/* regs r = rA, Z always 0*/
}

/*--------------------------------------------------*/
/* rotates reg 1 bit left, reg[7]->CY, CY->reg[0] */
void lrot(uint8_t* reg, int is_ra, uint8_t* flags) {
	uint8_t cy = *reg >> 7;
	*reg = (*reg << 1) | ((*flags & 0x10) >> 4);

	/* set flags */
	*flags = 0 | (cy << 4);	/* set CY */
	*flags = is_ra == 1 ? *flags : *flags | ((!*reg) << 7);	/* regs r = rA, Z always 0*/
}

/*--------------------------------------------------*/
/* rotates reg 1 bit right, stores reg[0] in CY, reg[0]->reg[7] */
void rrc(uint8_t* reg, int is_ra, uint8_t* flags) {
	uint8_t cy = *reg & 1;
	*reg = (*reg >> 1) | (cy << 7);

	/* set flags */
	*flags = 0 | (cy << 4);	/* set CY */
	*flags = is_ra == 1 ? *flags : *flags | ((!*reg) << 7);	/* ira == 1->reg == rA, Z always 0*/
}

/*--------------------------------------------------*/
/* rotates reg 1 bit right, reg[0]->CY, CY->reg[7] */
void rrot(uint8_t* reg, int is_ra, uint8_t* flags) {
	uint8_t cy = *reg & 1;
	*reg = (*reg >> 1) | (*flags & 0x10) << 3;

	/* set flags */
	*flags = 0 | (cy << 4);	/* set CY */
	*flags = is_ra == 1 ? *flags : *flags | ((!*reg) << 7);	/* ira == 1->reg == rA, Z always 0*/
}

/*--------------------------------------------------*/
/* combines two 8-bit values into 16-bit virtual address */
/* returns the address of location in memory buffer referred to by virtual address */
uint8_t* deref(uint8_t* ram, uint8_t high, uint8_t low) {
	int addr = (high << 8) + low;
	return &ram[addr];
}

/*--------------------------------------------------*/
/* fetches next byte in program counter and increments pc */
uint8_t fetch8(uint8_t* ram, uint16_t* pc) {
	uint8_t val = ram[*pc];
	*pc++;
	return val;
}

/*--------------------------------------------------*/
/* fetches next 2 bytes in program counter and increments pc */
uint16_t fetch16(uint8_t* ram, uint16_t* pc) {
	uint16_t val = (uint16_t)(ram[*pc + PROG_START] << 8);
	*pc++;
	val = val + ram[*pc];
	*pc++;
	return val;
}