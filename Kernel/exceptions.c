#include "exeption.h"

static exception exceptions[32] = {zero_division, 0, 0, 0, overflow, 0, invalid_op_code};

void exceptionDispatcher(int exceptionID, uint64_t rsp) {
	if (exceptionID==0||exceptionID==4||exceptionID==6)
	{
		exceptions[exceptionID](rsp);
		printStackFrame(rsp);
	}
}
static void zero_division(uint64_t rsp) {
	printString("Zero division");
}
static void overflow(uint64_t rsp) {
	printString("Overflow exception: \n");
}
static void invalid_op_code(uint64_t rsp) {
	printString("Invalid opcode exception: \n");
}
void printStackFrame(uint64_t rsp) {

	exceptionStackFrame* exceptionInfo = (uint64_t*) rsp;

	printString("Instruction pointer: ");
	printHex(exceptionInfo->instruction_pointer);
	printChar('\n');

	printString("Code segment: ");
	printHex(exceptionInfo->code_segment);
	printChar('\n');

	printString("CPU flags: ");
	printHex(exceptionInfo->cpu_flags);
	printChar('\n');

	printString("Stack pointer: ");
	printHex(exceptionInfo->stack_pointer);
	printChar('\n');

	printString("Stack segment: ");
	printHex(exceptionInfo->stack_segment);
	printChar('\n');
}