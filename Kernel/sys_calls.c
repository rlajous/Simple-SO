#include "include/keyboardDriver.h"
#include "include/videoDriver.h"

extern int getSeconds();
extern int getMinutes();
extern int getHours();
typedef void (*fn)(char* buffer, int size);

static fn sysCalls[3];


void sys_clear(char* buffer, int size){
	clear();
}

void sys_write(char* buffer, int size){
	char* c=buffer;
	for (int i = 0; i < size; i++)
	{
		printChar(*(c+i));
	}
}
void sys_read(char* buffer, int size){
	for (int i = 0; i < size; i++)
	{
		*(buffer + i) =get_buffer();
	}
}
void load_sys(){
	sysCalls[0]= &sys_clear;
	sysCalls[1]= &sys_write;
	sysCalls[2]= &sys_write;
}
void sys_handler(int num,char*buffer,int size){
	if (num>=0&&num<=3){
		sysCalls[num](buffer,size);
	}
	return;
}