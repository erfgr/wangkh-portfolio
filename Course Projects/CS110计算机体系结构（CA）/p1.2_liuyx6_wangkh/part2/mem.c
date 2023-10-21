#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "mem.h"


/*******************************
 * Helper Functions
 *******************************/

/* Call this function in the following cases:
        1. Attempts to access a memory location that it is not allowed to access.
        2. Attempts to access a memory location in a way that is not allowed.
 */
static void raise_segmentation_fault(Address addr) {
    write_to_log("Error - segmentation fault at address %08x\n", addr);
}

/* Call this function if a data access is performed to an address 
   that is not aligned for the size of the access.
 */
static void raise_alignment_fault(Address addr) {
    write_to_log("Error - alignment fault at address %08x\n", addr);
}

/* This function is helpful to your alignment check.
 */
int check_alignment(Address address, Alignment alignment) {
    if (alignment == LENGTH_BYTE)
    {
        return 1;
    }
    /* HALF_WORD: The last bit is not used. */
    else if (alignment == LENGTH_HALF_WORD)
    {
        return address % 2 == 0;
    }
    /* WORD: The last two bits are not used. */
    else if (alignment == LENGTH_WORD)
    {
        return address % 4 == 0;
    }
    else {
        return 0;
    }
}

/* To store the data in the corresponding address in memory, 
   please note the following points:
        1. When check_align==1, check if the memory address is aligned
         with the data type. You need to use raise_alignment_fault().
        2. Think about when you need to use raise_segmentation_fault().
        3. Please perform an address conversion before actually store to memory.
 */

void store(Byte *memory, Address address, Alignment alignment, Word value,
           int check_align)
{
    /* YOUR CODE HERE */
    unsigned int Physical_Memory = 0;
    /* check if has segmentation fault */	
	if( (address < 0x10000000) ||
		(address >= 0x10040000 && address < 0x7ff80000) ||
		address >= 0x7ffffffc){
		raise_segmentation_fault(address);
		return;
	}
	
	/* match physical memory */
	/* data_base -> memory_data */
	if(address >= 0x10000000 && address <= 0x10040000){
		Physical_Memory = address - 0x0ffc0000;
	}
	/* stack_base -> memory_stack */
	if(address >= 0x7ff80000 && address <= 0x7ffffffc){
		Physical_Memory = address - 0x7ff00000;
	}
	/* check if has alignment fault */
	if(check_align){
    	if(!check_alignment(address, alignment)){
    		raise_alignment_fault(Physical_Memory);
    		return;
		}
	}
	
	/* store byte */
	if(alignment == LENGTH_BYTE){
		memory[Physical_Memory] = value & 0x000000ff;
		return;
	}
	/* store half word */
	if(alignment == LENGTH_HALF_WORD){
		memory[Physical_Memory] = value & 0x000000ff;
		memory[Physical_Memory + 1] = (value >> 8) & 0x000000ff;
		return;
	}
	/* store word */
	if(alignment == LENGTH_WORD){
		memory[Physical_Memory] = value & 0x000000ff;
		memory[Physical_Memory + 1] = (value >> 8) & 0x000000ff;
		memory[Physical_Memory + 2] = (value >> 16) & 0x000000ff;
		memory[Physical_Memory + 3] = (value >> 24) & 0x000000ff;
		return;
	}
	raise_segmentation_fault(Physical_Memory);
	return;
}

/* To load the data in the corresponding address in memory, 
   please note the following points:
        1. When check_align==1, check if the memory address is aligned
         with the data type. You need to use raise_alignment_fault().
        2. Think about when you need to use raise_segmentation_fault().
        3. Please perform an address conversion before actually load from memory.
 */
Word load(Byte *memory, Address address, Alignment alignment, int check_align)
{
    /* YOUR CODE HERE */
    unsigned int Physical_Memory = 0;
    Word value = 0;
    /* check if has segmentation fault */	
	if(	(address > 0x00040000 && address < 0x10000000) ||
		(address >= 0x10040000 && address < 0x7ff80000) ||
		address > 0x7ffffffc){
		raise_segmentation_fault(address);
		return 0;
	}
	
	/* match physical memory */
	/* text_base -> memory_text */
	if(address <= 0x00040000){
		Physical_Memory = address;
	}
	/* data_base -> memory_data */
	if(address >= 0x10000000 && address <= 0x10040000){
		Physical_Memory = address - 0x0ffc0000;
	}
	/* stack_base -> memory_stack */
	if(address >= 0x7ff80000 && address <= 0x7ffffffc){
		Physical_Memory = address - 0x7ff00000;
	}
	/* check if has alignment fault */
	if(check_align){
    	if(!check_alignment(address, alignment)){
    		raise_alignment_fault(Physical_Memory);
    		return 0;
		}
	}
	/* load byte */
	if(alignment == LENGTH_BYTE){
		value = *((Byte *)(memory + Physical_Memory));
		return value;
	}
	/* load half word */
	if(alignment == LENGTH_HALF_WORD){
		value = *((Half *)(memory + Physical_Memory));
		return value;
	}
	/* load word */
	if(alignment == LENGTH_WORD){
		value = *((Word *)(memory + Physical_Memory));
		return value;
	}
	raise_segmentation_fault(Physical_Memory);
	return 0;
}
