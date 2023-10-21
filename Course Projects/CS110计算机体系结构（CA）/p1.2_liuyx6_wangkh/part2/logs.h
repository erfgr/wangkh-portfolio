#ifndef LOGS_H
#define LOGS_H

#include "emulator.h"
#include "mem.h"


/* Complete the following definition of Logs and implement the following
   functions. You are free to add structs or functions, but you must keep
   structure Logs. And you cannot change a function that has already been given.
 */

 /* Add structure definition here if you need */
 
typedef struct node{
	struct node *pre; /* previous node */
	Register reg[32]; /* registers */
	int mem_flag; /* if memories have been modified */
	Register PC; /* PC */
	Alignment alignment; /* alignment */
	Address address; /* address */
	Word value; /* value */
} LogData;
 
typedef struct
{
    /* YOUR CODE HERE */
    LogData *FinalNode;
} Logs;

/* IMPLEMENT ME - see documentation in logs.c */
Logs *create_logs();

/* IMPLEMENT ME - see documentation in logs.c */
void free_logs(Logs *logs);

/* IMPLEMENT ME - see documentation in logs.c */
void record(Instruction inst, Processor *cpu, Byte *mem, Logs *logs);

/* IMPLEMENT ME - see documentation in logs.c */
int undo(Processor *cpu, Byte *mem, Logs *logs);

/* Add function declaration here if you need */
void free_list(LogData *data);

LogData *build(Processor *cpu, LogData *final);

#endif