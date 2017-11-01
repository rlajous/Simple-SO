#include <include/keyboardDriver.h>
#include <include/videoDriver.h>

extern int getSeconds();
extern int getMinutes();
extern int getHours();

void sys_clear(){
	clear();
}

void sys_write(char* buffer, int size){
	char* c=buffer;
	for (int i = 0; i < size; i++)
	{
		printChar(c+i);
	}
}
void sys_read(char* buffer, int size){
	for (int i = 0; i < size; i++)
	{
		buffer + i =get_buffer();
	}
}