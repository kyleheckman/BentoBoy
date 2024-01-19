#include "gb_isa.h"
#define PROG_START 0x150

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
ld_sp(uint16_t* sp, uint16_t val) {
    *sp = val;
}

/*--------------------------------------------------*/
/* increments 8-bit register dest by 1 */
void inc_8(uint8_t* dest, uint8_t* flags) {
	*dest = *dest + 1;
	
	/* set flags */
	*flags = (*flags & 0x70) | (!*dest << 7);				                /* set Z flag */
	*flags = (*flags & 0xd0) | (((*dest ^ (*dest - 1) ^ 1) & 0x10) << 1);	/* set H flag */
	*flags = *flags & 0xb0;							                        /* unset N flag */
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
	*flags = (*flags & 0x70) | (!*dest << 7);				            /* set Z flag */
	*flags = (*flags & 0xd0) | (((int)((*dest+1) & 0xf) - 1 < 0) << 5);	/* set H flag */
	*flags = *flags | 0x40;							                    /* set N flag */
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
	*flags = (*flags & 0xe0) | (((int)(d16 + s16) > val) << 4);	    /* set CY flag */
	*flags = (*flags & 0xd0) | (((d16 ^ s16 ^ val) & 0x100) >> 3);	/* set H flag */
	*flags = *flags & 0xb0;						                    /* unset N flag */
}

/*--------------------------------------------------*/
/* add value of sp to 16-bit reg pair dest */
void add_sp_to(uint8_t* dest, uint16_t sp, uint8_t flags) {
	uint16_t d16 = (uint16_t)((*dest << 8) + *(dest+1));
	uint16_t val = d16 + sp;
	ld_16(dest, val);

	/* set flags */
	*flags = (*flags & 0xe0) | (((int)(d16 + sp) > val) << 4);	    /* set CY flag */
	*flags = (*flags & 0xd0) | (((d16 ^ sp ^ val) & 0x100) >> 3);	/* set H flag */
	*flags = *flags & 0xb0;						                    /* unset N flag */
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
	*flags = (*flags & 0x70) | (!*dest << 7);								/* set Z flag */
	*flags = *flags | 0x40;													/* set N flag */
	*flags = (*flags & 0xd0) | (((uint8_t)((old & 0xf) - ((src + cy) & 0xf)) & 0x10) << 1);	/* set H flag */
	*flags = (*flags & 0xe0) | (((int)(old - src - cy) < 0) << 4);		/* set CY flag */
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
/* rotates reg A 1 bit left, stores A[7] in CY */
/*void rlca() {
	uint8_t cy = regs[0] >> 7;
	regs[0] = (regs[0] << 1) | cy;
	flags = flags & ((cy << 7) | 0x70);
}*/

/*--------------------------------------------------*/
/* rotates reg A 1 bit right, stores A[0] in CY
void rrca() {
	uint8_t cy = (regs[0] & 1) << 7;
	regs[0] = (regs[0] >> 1) | cy;
	flags = flags & (cy | 0x70);
}*/

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
	uint8_t val = ram[*pc + PROG_START];
	*pc++;
	return val;
}

/*--------------------------------------------------*/
/* fetches next 2 bytes in program counter and increments pc */
uint16_t fetch16(uint8_t* ram, uint16_t* pc) {
	uint16_t val = (uint16_t)(ram[*pc + PROG_START] << 8);
	*pc++;
	val = val + ram[*pc + PROG_START];
	*pc++;
	return val;
}