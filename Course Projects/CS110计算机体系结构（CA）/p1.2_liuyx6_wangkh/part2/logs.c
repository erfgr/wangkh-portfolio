#include <stdlib.h>
#include <string.h>
#include "logs.h"
#include "execute_utils.h"


/*******************************
 * Helper Functions
 *******************************/

/* Creates a new empty Logs and returns a pointer to that Logs. 
   If memory allocation fails, you should call allocation_failed().
 */
Logs *create_logs() {
    /* YOUR CODE HERE */
    Logs *logs = malloc(sizeof(Logs));
    if(!logs){
    	allocation_failed();
	}
	logs -> FinalNode = NULL;
	return logs;
}

/* Frees the given Logs and all associated memory. */
void free_logs(Logs *logs) {
    /* YOUR CODE HERE */
    free_list(logs -> FinalNode);
    free(logs);
}

/* Record the current status and save in a logs component.
   Think about what information needs to be recorded.
   Logs can resize to fit an arbitrary number of entries. 
   (so you should use dynamic memory allocation).
 */
void record(Instruction inst, Processor *cpu, Byte *mem, Logs *logs)
{
    /* YOUR CODE HERE */
    Word val = 0;
    unsigned int Physical_Memory = 0;
    Address address = 0;
    LogData *tmp = build(cpu, logs -> FinalNode);
    
	/* if not Stype */
	if(inst.opcode.opcode != 0x23){
		logs -> FinalNode = tmp;
		return;
	}
	/* memories need to be modified */
	address = cpu -> reg[inst.stype.rs1] + get_store_offset(inst);
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
	/* illegal condition */
	if( (address >= 0x00040000 && address < 0x10000000) ||
		(address >= 0x10040000 && address < 0x7ff80000) ||
		address >= 0x7ffffffc){
		logs -> FinalNode = tmp;
		return;
	}
	
	switch(inst.stype.funct3){
		case 0: /* sb */
			if(!check_alignment(address, LENGTH_BYTE)){
				logs -> FinalNode = tmp;
				/* alignment fault */
				return;
			}
			val = *((Byte *)(mem + address));
			logs -> FinalNode -> alignment = LENGTH_BYTE;
			break;
		case 1: /* sh */
			if(!check_alignment(address, LENGTH_HALF_WORD)){
				logs -> FinalNode = tmp;
				/* alignment fault */
				return;
			}
			val = *((Half *)(mem + address));
			logs -> FinalNode -> alignment = LENGTH_HALF_WORD;
			break;
		case 2: /* sw */
			if(!check_alignment(address, LENGTH_WORD)){
				logs -> FinalNode = tmp;
				/* alignment fault */
				return;
			}
			val = *((Word *)(mem + address));
			logs -> FinalNode -> alignment = LENGTH_WORD;
			break;
		default:
			/* illegal condition */
			logs -> FinalNode = tmp;
			return;
			break;
	}
	/* update information */
	logs -> FinalNode -> address = Physical_Memory;
	logs -> FinalNode -> value = val;
	logs -> FinalNode -> mem_flag = 1;
	logs -> FinalNode = tmp;
}

/* Back to the previous state recorded in a logs component.
   if success, return 0.
   if fail, for example, no previous state, return -1.
 */
int undo(Processor *cpu, Byte *mem, Logs *logs) {
    /* YOUR CODE HERE */
    int i;
    LogData *tmp = logs -> FinalNode;
    /* no previou node */
    if(!logs -> FinalNode){
    	return -1;
	}
	/* move forward */
    logs -> FinalNode = logs -> FinalNode -> pre;
    /* restore registers */
    for(i = 0 ; i < 32 ; i++){
    	cpu -> reg[i] = tmp -> reg[i];
	}
	/* restore PC */
	cpu -> PC = tmp -> PC;
	if(tmp -> mem_flag){
		/* memories have been modified */
		switch(tmp -> alignment){
			case LENGTH_BYTE:
				/* byte */
				mem[tmp -> address] = tmp -> value & 0x000000ff;
				break;
			case LENGTH_HALF_WORD:
				/* half */
				mem[tmp -> address] = tmp -> value & 0x000000ff;
				mem[tmp -> address + 1] = (tmp -> value >> 8) & 0x000000ff;
				break;
			case LENGTH_WORD:
				/* word */
				mem[tmp -> address] = tmp -> value & 0x000000ff;
				mem[tmp -> address + 1] = (tmp -> value >> 8) & 0x000000ff;
				mem[tmp -> address + 2] = (tmp -> value >> 16) & 0x000000ff;
				mem[tmp -> address + 3] = (tmp -> value >> 24) & 0x000000ff;
				break;
			default:
				break;
		}
	}
	/* free node */
	free(tmp);
	return 0;
}

/* Add function definition here if you need */
void free_list(LogData *data){
	if(data && data -> pre){
		free_list(data -> pre);
	}
	free(data);
}

LogData *build(Processor *cpu, LogData *final){
	int i;
	LogData* node = (LogData *)malloc(sizeof(LogData));
	/* illegal condition */
	if(!node) allocation_failed();
	node -> pre = final;
	node -> mem_flag = 0;
	/* store registers*/
	for(i = 0 ; i < 32 ; i++){
		node -> reg[i] = cpu -> reg[i];
	}
	node -> PC = cpu -> PC;
	return node;
}
