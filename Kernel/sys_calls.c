#include "include/keyboardDriver.h"
#include "include/videoDriver.h"

extern int getSeconds();
extern int getMinutes();
extern int getHours();

typedef void (*fn)(unsigned long rsi, unsigned long rdx, unsigned long rcx, unsigned long r8, unsigned long r9);

static fn sysCalls[5];

void sys_time(unsigned long sec, unsigned long min, unsigned long hour, unsigned long month, unsigned long year){
	sec=getSeconds();
	min=getMinutes();
	hour=getHours();
}
void sys_clear(unsigned long rsi, unsigned long rdx, unsigned long rcx, unsigned long r8, unsigned long r9){
	clear();
}

void sys_write(unsigned long buffer, unsigned long size, unsigned long rcx, unsigned long r8, unsigned long r9){
	char* c=(char*)buffer;
	for (int i = 0; i < size; i++)
	{
		printChar(*(c+i));
	}
}
void sys_setTerminal(unsigned long size, unsigned long rdx, unsigned long rcx, unsigned long r8, unsigned long r9){
	setTerminal((int)size);
}
void sys_read(unsigned long buffer, unsigned long size, unsigned long rcx, unsigned long r8, unsigned long r9){
	char * buff=(char*)buffer;
	for (int i = 0; i < size; i++)
	{
		*(buff + i) =get_buffer();
	}
}
void load_sys(){
	sysCalls[0]= &sys_clear;
	sysCalls[1]= &sys_write;
	sysCalls[2]= &sys_read;
	sysCalls[3]= &sys_setTerminal;
	sysCalls[4]= &sys_time;
}
//rdi, rsi, rdx, rcx, r8 y r9
void sys_handler(unsigned long rdi, unsigned long rsi, unsigned long rdx, unsigned long rcx, unsigned long r8, unsigned long r9){
	if (rsi>=0&&rsi<=3){
		sysCalls[rdi](rsi,rdx,rcx,r8,r9);
	}
	return;
}