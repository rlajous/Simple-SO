#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H

#include <stdint.h>

static void zero_division();
static void overflow();
static void invalid_op_code();
void printStackFrame(uint64_t rsp);
//void load_exeptions();

typedef void (* exception)(uint64_t rsp);

#pragma pack(push)		
#pragma pack (1) 		
//https://os.phil-opp.com/better-exception-messages/
typedef struct {
  uint64_t instruction_pointer;
  uint64_t code_segment;
  uint64_t cpu_flags;
  uint64_t stack_pointer;
  uint64_t stack_segment;
} exceptionStackFrame;

#pragma pack(pop)	

#endif