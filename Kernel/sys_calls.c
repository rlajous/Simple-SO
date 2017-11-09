#include "include/keyboardDriver.h"
#include "include/videoDriver.h"
#include "kernel.h"

extern int getSeconds();
extern int getMinutes();
extern int getHours();
extern int getMonth();
extern int getYear();


typedef void (*fn)(unsigned long rsi, unsigned long rdx, unsigned long rcx, unsigned long r8, unsigned long r9);

static fn sysCalls[9];

void sys_time(unsigned long sec, unsigned long min, unsigned long hour, unsigned long month, unsigned long year){
	int *segundos=(int *)sec;
	int *minutos=(int *)min;
	int *horas=(int *)hour;
	int *meses=(int *)month;
	int *anos=(int *)year;
	(*segundos)=getSeconds();
	(*minutos)=getMinutes();
	(*horas)=getHours();
	//(*meses)=getMonth();
	//(*anos)=getYear();
}
void sys_clear(unsigned long rsi, unsigned long rdx, unsigned long rcx, unsigned long r8, unsigned long r9){
	clear();
}

void sys_write(unsigned long buffer, unsigned long size, unsigned long rcx, unsigned long r8, unsigned long r9){
	char* c=(char*)buffer;
	for (int i = 0; i < size; i++)
	{
		printChar(c[i]);
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
void sys_graphic(unsigned long color, unsigned long x, unsigned long y, unsigned long r8, unsigned long r9){
	//printPixel((int)buffer);
	putPixelAt((int)color,(int)x,(int)y);
}

void sys_resolution(unsigned long height, unsigned long width, unsigned long rcx, unsigned long r8, unsigned long r9){
	getResolution((int *)height,(int *)width);
	//(int)
}

void sys_backspace(unsigned long rsi, unsigned long rdx, unsigned long rcx, unsigned long r8, unsigned long r9){
	backspace();
}

void sys_newline(unsigned long rsi, unsigned long rdx, unsigned long rcx, unsigned long r8, unsigned long r9){
	newline();
}

void load_sys(){
	sysCalls[0]= &sys_clear;
	sysCalls[1]= &sys_write;
	sysCalls[2]= &sys_read;
	sysCalls[3]= &sys_setTerminal;
	sysCalls[4]= &sys_time;
	sysCalls[5]= &sys_graphic;
	sysCalls[6]= &sys_resolution;
	sysCalls[7]= &sys_backspace;
	sysCalls[8]= &sys_newline;
}
//rdi, rsi, rdx, rcx, r8 y r9
void sys_handler(unsigned long rdi, unsigned long rsi, unsigned long rdx, unsigned long rcx, unsigned long r8, unsigned long r9){
	if (rdi>=0&&rdi<=6){
		sysCalls[rdi](rsi,rdx,rcx,r8,r9);
	}
	return;
}