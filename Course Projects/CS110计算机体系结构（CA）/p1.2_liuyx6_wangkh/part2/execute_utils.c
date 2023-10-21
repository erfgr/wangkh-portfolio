#include <stdio.h>
#include <stdlib.h>
#include "execute_utils.h"


/* You may find implementing this function helpful */

/* Signed extension of a number to 32 bits. 
   size is the number of valid bits of field.
   e.g. field=0x8a, size=8, return 0xFFFFFF8a.
        field=0x7a, size=8, return 0x0000007a.
 */
int bitSigner(unsigned int field, unsigned int size)
{
    /* YOUR CODE HERE */
    unsigned sym = field & (1 << (size - 1));
    if(sym) sym = ~((1 << (size - 1)) - 1);
    return sym | field;
}

/* Return the imm from instruction, for details, please refer to I type instruction formats.
   Remember that the offsets should return the offset in BYTES.
 */
int get_imm_operand(Instruction instruction)
{
    /* YOUR CODE HERE */
    return bitSigner(instruction.itype.imm, 12);
}
/* Return the offset from instruction, for details, please refer to SB type instruction formats.
   Remember that the offsets should return the offset in BYTES.
 */
int get_branch_offset(Instruction instruction)
{
    /* YOUR CODE HERE */
    unsigned int imm12 = (instruction.sbtype.imm7 & 0x40) >> 6;
    unsigned int imm11 = instruction.sbtype.imm5 & 0x01;
    unsigned int imm10_5 = instruction.sbtype.imm7 & 0x3f;
    unsigned int imm4_1 = (instruction.sbtype.imm5 & 0x1e) >> 1;
    /* imm : 13 */
    unsigned int imm = (imm12 << 12) + (imm11 << 11) + (imm10_5 << 5) + (imm4_1 << 1);
    return bitSigner(imm, 13);
}

/* Return the offset from instruction, for details, please refer to UJ type instruction formats.
   Remember that the offsets should return the offset in BYTES.
 */
int get_jump_offset(Instruction instruction)
{
    /* YOUR CODE HERE */
    unsigned int imm20 = (instruction.ujtype.imm & 0x80000) >> 19;
    unsigned int imm19_12 = instruction.ujtype.imm & 0xff;
    unsigned int imm11 = (instruction.ujtype.imm & 0x100) >> 8;
    unsigned int imm10_1 = (instruction.ujtype.imm & 0x7fe00) >> 9;
    /* imm : 21 */
    unsigned int imm = (imm20 << 20) + (imm19_12 << 12) + (imm11 << 11) + (imm10_1 << 1);
    return bitSigner(imm, 21);
}

/* Return the offset from instruction, for details, please refer to S type instruction formats.
   Remember that the offsets should return the offset in BYTES.
 */
int get_store_offset(Instruction instruction)
{
    /* YOUR CODE HERE */
    unsigned int imm11_5 = instruction.stype.imm7;
    unsigned int imm4_0 = instruction.stype.imm5;
    /* imm : 12 */
    unsigned int imm = (imm11_5 << 5) + imm4_0;
    return bitSigner(imm, 12);
}