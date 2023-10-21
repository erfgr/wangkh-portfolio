/* This project is based on the MIPS Assembler of CS61C in UC Berkeley.
   The framework of this project is been modified to be suitable for RISC-V
   in CS110 course in ShanghaiTech University by Zhijie Yang in March 2019.
   Updated by Chibin Zhang and Zhe Ye in March 2021. Modified by Lei Jia 
   to be part of the project in Feb 2023.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "tables.h"

const int SYMBOLTBL_NON_UNIQUE = 0;
const int SYMBOLTBL_UNIQUE_NAME = 1;

/*******************************
 * Helper Functions
 *******************************/

void addr_alignment_incorrect()
{
    write_to_log("Error: address is not a multiple of 4.\n");
}

void name_already_exists(const char *name)
{
    write_to_log("Error: name '%s' already exists in table.\n", name);
}

void write_sym(FILE *output, uint32_t addr, const char *name)
{
    fprintf(output, "%u\t%s\n", addr, name);
}

/*******************************
 * Symbol Table Functions
 *******************************/

/* Creates a new SymbolTable containg 0 elements and returns a pointer to that
   table. Multiple SymbolTables may exist at the same time.
   If memory allocation fails, you should call allocation_failed().
   Mode will be either SYMBOLTBL_NON_UNIQUE or SYMBOLTBL_UNIQUE_NAME. You will
   need to store this value for use during add_to_table().
 */
SymbolTable *create_table(int mode)
{
    /* YOUR CODE HERE */
}

/* Frees the given SymbolTable and all associated memory. */
void free_table(SymbolTable *table)
{
    /* YOUR CODE HERE */
}

/* Adds a new symbol and its address to the SymbolTable pointed to by TABLE. 
   1. ADDR is given as the byte offset from the first instruction. 
   2. The SymbolTable must be able to resize itself as more elements are added. 

   3. Note that NAME may point to a temporary array, so it is not safe to simply
   store the NAME pointer. You must store a copy of the given string.

   4. If ADDR is not word-aligned and check_align==1, you should call 
   addr_alignment_incorrect() and return -1. 

   5. If the table's mode is SYMTBL_UNIQUE_NAME and NAME already exists 
   in the table, you should call name_already_exists() and return -1. 

   6.If memory allocation fails, you should call allocation_failed(). 

   Otherwise, you should store the symbol name and address and return 0. 
 */
int add_to_table(SymbolTable *table, const char *name, uint32_t addr, int check_align)
{
    /* YOUR CODE HERE */
}

/* Returns the address (byte offset) of the given symbol. If a symbol with name
   NAME is not present in TABLE, return -1.
 */
int64_t get_addr_for_symbol(SymbolTable *table, const char *name)
{
    /* YOUR CODE HERE */
}

/* Writes the SymbolTable TABLE to OUTPUT. You should use write_sym() to
   perform the write. Do not print any additional whitespace or characters.
 */
void write_table(SymbolTable *table, FILE *output)
{
    /* YOUR CODE HERE */
}

/* DO NOT MODIFY THIS LINE BELOW */
/* ===================================================================== */
/* Read the symbol table file written by the `write_table` function, and
   restore the symbol table.
 */
SymbolTable *create_table_from_file(int mode, FILE *file)
{
    SymbolTable *symtbl = create_table(mode);
    char buf[1024];
    while (fgets(buf, sizeof(buf), file))
    {
        char *name, *addr_str, *end_ptr;
        uint32_t addr;
        addr_str = strtok(buf, "\t");
        /* create table based on these tokens */
        addr = strtol(addr_str, &end_ptr, 0);
        name = strtok(NULL, "\n");
        /* add the name to table, one by one */
        add_to_table(symtbl, name, addr, 0);
    }
    return symtbl;
}