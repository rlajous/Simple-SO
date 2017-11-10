#include "exeption.h"

static exception exceptions[32];

void exceptionDispatcher(int exceptionID, uint64_t rsp) {
	if (exceptionID==0||exceptionID==4||exceptionID==6)
	{
		exceptions[exceptionID](rsp);
		printStackFrame(rsp);
	}
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
void load_exeptions(){
	exceptions[0]=zero_division;
	exceptions[4]=overflow;
	exceptions[6]=invalid_op_code;
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