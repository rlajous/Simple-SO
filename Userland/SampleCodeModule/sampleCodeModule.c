/* sampleCodeModule.c */
#include "syscalls.h"
#include "stdio.h"




int main() {
	//All the following code may be removed 
	//printf("User: ");
	//char buffer[500]={'0'};
	//Test if BSS is properly set up
	setVideo();
	shell();

//	int a, len;
//	char b;
//	char c[200];
//
//	printf("go on:\n");
//
//	len = scanf("%s, %c", c, &b);
//
//	if(len != 0){
//	
//	printf("%s, %c and lenght %d\n", c, b, len);
//	}else{
//		printf("no cumplis\n");
// }


	//printGraphic(1);
	//printGraphic(1);
	//printGraphic(0);
	//read(buffer, 2);
	//write(buffer,2);
	//time(&sec,&min,&hs,&month,&year);
	//write((char *)((sec%10)+'0'),1);
}
