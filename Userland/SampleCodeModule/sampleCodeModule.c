/* sampleCodeModule.c */
#include "syscalls.h"
#include <stdio.h>




int main() {
	//All the following code may be removed 
	
	//Test if BSS is properly set up
	setVideo();
	printf("llegue\n");
	shell();
	printf("pase\n");
	//printGraphic(1);
	//printGraphic(1);
	//printGraphic(0);
	//read(buffer, 2);
	//write(buffer,2);
	//time(&sec,&min,&hs,&month,&year);
	//write((char *)((sec%10)+'0'),1);
}
