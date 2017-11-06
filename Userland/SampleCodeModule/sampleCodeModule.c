/* sampleCodeModule.c */
#include "syscalls.h"

int main() {
	//All the following code may be removed 
	
	char buffer[500]={'0'};
	//Test if BSS is properly set up
	
	while(1){
	read(buffer, 2);
	write(buffer,2);
	//time(&sec,&min,&hs,&month,&year);
	//write((char *)((sec%10)+'0'),1);
	}
}