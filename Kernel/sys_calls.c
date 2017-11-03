#include "include/keyboardDriver.h"
#include "include/videoDriver.h"

extern int getSeconds();
extern int getMinutes();
extern int getHours();
typedef void (*fn)(unsigned long rdx, unsigned long rcx, unsigned long r8, unsigned long r9);

static fn sysCalls[3];


void sys_clear(unsigned long rdx, unsigned long rcx, unsigned long r8, unsigned long r9){
	clear();
}

void sys_write(unsigned long buffer, unsigned long rcx, unsigned long r8, unsigned long r9){
	char* c=(char*)buffer;
	for (int i = 0; i < size; i++)
	{
		printChar(*(c+i));
	}
}
void sys_read(unsigned long buffer, unsigned long size, unsigned long r8, unsigned long r9){
	buff=(char*)buffer;
	for (int i = 0; i < size; i++)
	{
		*(buff + i) =get_buffer();
	}
}
void load_sys(){
	sysCalls[0]= &sys_clear;
	sysCalls[1]= &sys_write;
	sysCalls[2]= &sys_write;
}
void sys_handler(unsigned long rsi, unsigned long rdx, unsigned long rcx, unsigned long r8, unsigned long r9){
	if (rsi>=0&&rsi<=3){
		sysCalls[rsi](rdx,rcx);
	}
	return;
}