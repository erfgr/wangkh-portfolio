#include <stdio.h>
#include "execute.h"
#include "execute_utils.h"
#include "mem.h"


/*******************************
 * Helper Functions
 *******************************/

/* Function handle with error machine code. You should skip the error 
   machine code after call this funcion
*/
void raise_machine_code_error(Instruction instruction){
    write_to_log("Invalid Machine Code: 0x%08x\n", instruction.bits);
}

/* Function handle with undefined ecall parameter.
*/
void raise_undefined_ecall_error(Register a0){
    write_to_log("Undefined Ecall Number: %d\n", a0);
}

/* Function to exit current program */
void exit_program(Processor *p) {
    if (p->stat==1) {
        /* set cpu state unwork */
        p->stat=0;
        write_to_log("Exited with error code 0.\n");
    }
    else {
        write_to_log("Error: program already exit.\n");
    }
}

/* 
    In this section you need to complete execute instruction. This should modify 
    the appropriate registers, make any necessary calls to memory, and updatge the program
    counter to refer You will find the functions in execute_utils.h very useful. So it's 
    better to finish execute_utils.c first. The following provides you with a general 
    framework. You can follow this framework or add your own functions, but please 
    don't change declaration or feature of execute(). Case execute() is the entry point
    to the execution phase. The execute_*() is specific implementations for each 
    instruction type. You had better read types.h carefully. Think about the usage 
    of the union defined in types.h
 */

void execute(Instruction inst, Processor *p, Byte *memory)
{
	p->reg[0] = 0;
    switch (inst.opcode.opcode)
    { 
    /* YOUR CODE HERE: COMPLETE THE SWITCH STATEMENTS */
    /* R type */
    case 0x33:
    	execute_rtype(inst, p);
    	/*go to next instruction*/
    	p->PC += 4;
    	break;
    
    /* Itype_except_load */
    case 0x13:
    	execute_itype_except_load(inst, p);
    	break;
    /* Itype ecall */
    case 0x73:
    	execute_ecall(p, memory);
    	break;
    /* SBtype branch */
    case 0x63:
    	execute_branch(inst, p);
    	break;
    /* Itype execute_load */
    case 0x03:
    	execute_load(inst, p, memory);
    	break;
    /* Stype execute_store */
    case 0x23:
    	execute_store(inst, p, memory);
    	break;
    /* UJtype execute_jal */
    case 0x6f:
    	execute_jal(inst, p);
    	break;
    /* Itype execute_jalr */
    case 0x67:
    	execute_jalr(inst, p);
    	break;
    /* Utype auipc execute_utype */
    case 0x17:
    	execute_utype(inst, p);
    	break;
    /* Utype lui execute_utype */
    case 0x37:
    	execute_utype(inst, p);
    	break;

    default: /* undefined opcode */
        raise_machine_code_error(inst);
        p->PC += 4;
        break;
    }
    return;
}

void execute_rtype(Instruction inst, Processor *p)
{
    sDouble result;
    switch (inst.rtype.funct3)
    {/* rtype */
    case 0x0: 
        switch (inst.rtype.funct7)
        {
        case 0x00: /* 0x0 add */
            p->reg[inst.rtype.rd] = p->reg[inst.rtype.rs1] + p->reg[inst.rtype.rs2];
            break;
        case 0x01: /* 0x1 mul */
            result = (sWord)p->reg[inst.rtype.rs1] * (sWord)p->reg[inst.rtype.rs2];
            p->reg[inst.rtype.rd] = (Word)result;
            break;
        case 0x20: /* 0x20 sub */
            p->reg[inst.rtype.rd] = p->reg[inst.rtype.rs1] - p->reg[inst.rtype.rs2];
            break;
        default:
            raise_machine_code_error(inst);
            break;
        }
        break;

    case 0x1: 
        switch (inst.rtype.funct7)
        {
        case 0x00: /* sll */
            p->reg[inst.rtype.rd] = p->reg[inst.rtype.rs1] << (p->reg[inst.rtype.rs2] & 0x1f);
            break;
        case 0x01: /* mulh */
            result = (sDouble)(sWord)p->reg[inst.rtype.rs1] * (sDouble)(sWord)p->reg[inst.rtype.rs2];
            p->reg[inst.rtype.rd] = (Word)(Double)(result >> 32);
            break;
        default:
            raise_machine_code_error(inst);
            break;
        }
        break;
    
    case 0x2:/* 0x2 slt */
    	if(inst.rtype.funct7 != 0x00){
    		/* illegal funct7 */
    		raise_machine_code_error(inst);
    		break;
		}
        p->reg[inst.rtype.rd] = ((sWord)p->reg[inst.rtype.rs1] < (sWord)p->reg[inst.rtype.rs2]) ? 1 : 0;
        break;

    case 0x3:/* 0x3 sltu */
    	if(inst.rtype.funct7 != 0x00){
    		/* illegal funct7 */
    		raise_machine_code_error(inst);
    		break;
		}
        p->reg[inst.rtype.rd] = ((Word)p->reg[inst.rtype.rs1] < (Word)p->reg[inst.rtype.rs2]) ? 1 : 0;
        break;

    case 0x4:
        switch (inst.rtype.funct7)
        {
        case 0x00: /* 0x0 xor */
            p->reg[inst.rtype.rd] = p->reg[inst.rtype.rs1] ^ p->reg[inst.rtype.rs2];
            break;
        case 0x01: /* 0x1 div */
            p->reg[inst.rtype.rd] = (sWord)p->reg[inst.rtype.rs1] / (sWord)p->reg[inst.rtype.rs2];
            break;
        default:
            raise_machine_code_error(inst);
            break;
        }
        break;
    
    case 0x5:
        switch (inst.rtype.funct7)
        {
        case 0x00: /* 0x0 srl */
            p->reg[inst.rtype.rd] = p->reg[inst.rtype.rs1] >> (p->reg[inst.rtype.rs2] & 0x1f);
            break;
        case 0x20: /* 0x20 sra */
            p->reg[inst.rtype.rd] = (sWord)p->reg[inst.rtype.rs1] >> (p->reg[inst.rtype.rs2] & 0x1f);
            break;
        default:
            raise_machine_code_error(inst);
            break;
        }
        break;

    case 0x6:
        switch (inst.rtype.funct7)
        {
        case 0x00: /* 0x0 or */
            p->reg[inst.rtype.rd] = p->reg[inst.rtype.rs1] | p->reg[inst.rtype.rs2];
            break;
        case 0x01: /* 0x1 rem */
            p->reg[inst.rtype.rd] = (sWord)p->reg[inst.rtype.rs1] % (sWord)p->reg[inst.rtype.rs2];
            break;
        default:
            raise_machine_code_error(inst);
            break;
        }
        break;

    case 0x7:
        switch (inst.rtype.funct7)
        {
        case 0x00: /* 0x0 and */
        	if(inst.rtype.funct7 != 0x00){
        		/* illegal funct7 */
	    		raise_machine_code_error(inst);
	    		break;
			}
            p->reg[inst.rtype.rd] = p->reg[inst.rtype.rs1] & p->reg[inst.rtype.rs2];
            break;
        default:
            raise_machine_code_error(inst);
            break;
        }
        break;
    /*undefined funct3*/
    default:
        raise_machine_code_error(inst);
        break;
    }
	return;
}

void execute_itype_except_load(Instruction inst, Processor *p)
{
    /* YOUR CODE HERE */
    switch(inst.itype.funct3)
    {
    case 0x0: /* 0x0 addi */
        p->reg[inst.itype.rd] = p->reg[inst.itype.rs1] + get_imm_operand(inst);
        break;

    case 0x1: /* 0x1 slli */
        p->reg[inst.itype.rd] = p->reg[inst.itype.rs1] << get_imm_operand(inst);
        break;

    case 0x2: /* 0x2 slti */
        p->reg[inst.itype.rd] = ((sWord)p->reg[inst.itype.rs1] < (sWord)get_imm_operand(inst)) ? 1 : 0;
        break;

    case 0x3: /* 0x3 sltiu */
        p->reg[inst.itype.rd] = ((Word)p->reg[inst.itype.rs1] < (Word)get_imm_operand(inst)) ? 1 : 0;
        break;

    case 0x4: /* 0x4 xori */
        p->reg[inst.itype.rd] = p->reg[inst.itype.rs1] ^ get_imm_operand(inst);
        break;

    case 0x5:
        switch (inst.rtype.funct7)
        {
        case 0x00: /* 0x0 srli */
            p->reg[inst.itype.rd] = p->reg[inst.itype.rs1] >> get_imm_operand(inst);
            break;
        case 0x20: /* 0x20 srai */
            p->reg[inst.itype.rd] = (sWord)p->reg[inst.itype.rs1] >> (get_imm_operand(inst));
            break;
        default:
            raise_machine_code_error(inst);
            break;
        }
        break;

    case 0x6: /* 0x6 ori */
        p->reg[inst.itype.rd] = p->reg[inst.itype.rs1] | get_imm_operand(inst);
        break;

    case 0x7: /* 0x7 andi */
        p->reg[inst.itype.rd] = p->reg[inst.itype.rs1] & get_imm_operand(inst);
        break;

    default:
        raise_machine_code_error(inst);
        break;
    }
    /*go to next instruction*/
    p->PC += 4;
	return;
}

/* You may need to use exit_program() */
void execute_ecall(Processor *p, Byte *memory)
{
	unsigned int Physical_Memory = 0;
	Address address = p -> reg[11];
	/* match physical memory */
	/* text_base -> memory_text */
	if(address < 0x00040000){
		Physical_Memory = address;
	}
	/* data_base -> memory_data */
	if(address >= 0x10000000 && address < 0x10040000){
		Physical_Memory = address - 0x0ffc0000;
	}
	/* stack_base -> memory_stack */
	if(address >= 0x7ff80000 && address <= 0x7ffffffc){
		Physical_Memory = address - 0x7ff00000;
	}
    switch(p->reg[10])
    {
    case 1: /* print integer | a1(x11) */
        write_to_log("%d", p->reg[11]);
        break;

    case 4: /* print string */
    	write_to_log("%s",(char *)(memory + (Address)Physical_Memory));
        break;

    case 10: /* exit */
        exit_program(p);
        break;

    case 11: /* print character */
        write_to_log("%c", p->reg[11]);
        break;

    default:
        raise_undefined_ecall_error(p->reg[10]);
        break;
    }
    /*go to next instruction*/
    p->PC += 4;
	return;
}

void execute_branch(Instruction inst, Processor *p)
{
    /* YOUR CODE HERE */
    int offset = 4;
    switch(inst.sbtype.funct3)
    {
    case 0x0: /* 0x0 beq */
        if (p->reg[inst.sbtype.rs1] == p->reg[inst.sbtype.rs2])
        {offset = get_branch_offset(inst);}
        else
        {offset = 4;}
        break;

    case 0x1: /* 0x1 bne */
        if (p->reg[inst.sbtype.rs1] != p->reg[inst.sbtype.rs2])
        {offset = get_branch_offset(inst);}
        else
        {offset = 4;}
        break;

    case 0x4: /* 0x4 blt */
        if ((sWord)p->reg[inst.sbtype.rs1] < (sWord)p->reg[inst.sbtype.rs2])
        {offset = get_branch_offset(inst);}
        else
        {offset = 4;}
        break;

    case 0x5: /* 0x5 bge */
        if ((sWord)p->reg[inst.sbtype.rs1] >= (sWord)p->reg[inst.sbtype.rs2])
        {offset = get_branch_offset(inst);}
        else
        {offset = 4;}
        break;

    case 0x6: /* 0x6 bltu */
        if ((Word)p->reg[inst.sbtype.rs1] < (Word)p->reg[inst.sbtype.rs2])
        {offset = get_branch_offset(inst);}
        else
        {offset = 4;}
        break;

    case 0x7: /* 0x7 bgeu */
        if ((Word)p->reg[inst.sbtype.rs1] >= (Word)p->reg[inst.sbtype.rs2])
        {offset = get_branch_offset(inst);}
        else
        {offset = 4;}
        break;
    /* default: */
    default:
        raise_machine_code_error(inst);
        offset = 4;
        break;
    }
    /*go to next instruction*/
    p->PC += offset;
	return;
}

void execute_load(Instruction inst, Processor *p, Byte *memory)
{
    /* YOUR CODE HERE */
    Word value = 0;
    switch(inst.itype.funct3)
    {
    case 0x0: /* 0x0 lb */
        value = load(memory, p->reg[inst.itype.rs1] + get_imm_operand(inst), LENGTH_BYTE, 1);
        p->reg[inst.itype.rd] = bitSigner(value, 8);
        break;

    case 0x1: /* 0x1 lh */
        value = load(memory, p->reg[inst.itype.rs1] + get_imm_operand(inst), LENGTH_HALF_WORD, 1);
        p->reg[inst.itype.rd] = bitSigner(value, 16);
        break;

    case 0x2: /* 0x2 lw */
        value = load(memory, p->reg[inst.itype.rs1] + get_imm_operand(inst), LENGTH_WORD, 1);
        p->reg[inst.itype.rd] = bitSigner(value, 32);
        break;

    case 0x4: /* 0x4 lbu */
        p->reg[inst.itype.rd] = load(memory, p->reg[inst.itype.rs1] + get_imm_operand(inst), LENGTH_BYTE, 1);
        break;

    case 0x5: /* 0x5 lhu */
        p->reg[inst.itype.rd] = load(memory, p->reg[inst.itype.rs1] + get_imm_operand(inst), LENGTH_HALF_WORD, 1);
        break;

    default:
        raise_machine_code_error(inst);
        break;
    }
    /*go to next instruction*/
    p->PC += 4;
	return;
}

void execute_store(Instruction inst, Processor *p, Byte *memory)
{
    /* YOUR CODE HERE */
    switch(inst.stype.funct3)
    {
    case 0x0: /* 0x0 sb */
        store(memory, p->reg[inst.stype.rs1] + get_store_offset(inst), LENGTH_BYTE, p->reg[inst.stype.rs2], 1);
        break;

    case 0x1: /* 0x1 sh */
        store(memory, p->reg[inst.stype.rs1] + get_store_offset(inst), LENGTH_HALF_WORD, p->reg[inst.stype.rs2], 1);
        break;

    case 0x2: /* 0x2 sw */
        store(memory, p->reg[inst.stype.rs1] + get_store_offset(inst), LENGTH_WORD, p->reg[inst.stype.rs2], 1);
        break;
    
    default:
        raise_machine_code_error(inst);
        break;
    }
    /*go to next instruction*/
    p->PC += 4;
	return;
}

void execute_jal(Instruction inst, Processor *p)
{
    /* YOUR CODE HERE */
    /*set rd to PC + 4*/
    p->reg[inst.ujtype.rd] = p->PC + 4;
    /*set PC to PC + imm*/
    p->PC += get_jump_offset(inst);
	return;
}

void execute_jalr(Instruction inst, Processor *p)
{
    /* YOUR CODE HERE */
    Word value = 0;
    /*get value of rs1*/
    value = p->reg[inst.itype.rs1];
    /*set rd to PC + 4*/
    p->reg[inst.itype.rd] = p->PC + 4;
    /*set PC to value + imm*/
    p->PC = value + get_imm_operand(inst);
	return;
}

void execute_utype(Instruction inst, Processor *p)
{
    /* YOUR CODE HERE */
    switch(inst.utype.opcode)
    {
    case 0x37: /* 0x37 lui*/
    	p->reg[inst.utype.rd] = inst.utype.imm << 12;
        break;

    case 0x17: /* 0x17 auipc */
        p->reg[inst.utype.rd] = p->PC + (inst.utype.imm << 12);
        break;

    default:
        raise_machine_code_error(inst);
        break;
    }
    /*go to next instruction*/
    p->PC += 4;
	return;
}