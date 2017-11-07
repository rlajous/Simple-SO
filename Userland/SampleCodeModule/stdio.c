#include "syscalls.h"
#include "stdlib.h"
#include <stdarg.h>

void putchar(char letter){
	write(&letter, 1);
}

char getchar(){
	char letter;
	do {
		read(&letter, 1);
	}while(letter == -1);
	return letter;
}

int printf(const char* format, ...){
	va_list args; //lista de argumentos variables 
	va_start(args, format); // dice que la lista de args empieza despues de formato
	//va_arg(args, (tipo de dato))
	char* index = format;
	char buffer[12];
	char* str;
	int len, num;
	while(*(index) != 0){
		if(*(index) == '%'){
			switch(*(index+1)){
				case 'd':
					num = (int) va_arg(args, int);
					len = itoa(num, buffer, 10);
					write(buffer, len);
					index++;
					break;
				case 'c':
					putchar((char) va_arg(args, int));
					index++;
					break;
				case 's': 
					str = (char*) va_arg(args, char*);
					write(str, strlen(str));
					index++;

			}
			index++;
		}else{
			putchar(*(index));
		}
		index++;
		
	}
	return 0;
}

int scanf(const char* format, ...){
	va_list args; //lista de argumentos variables 
	va_start(args, format); // dice que la lista de args empieza despues de format
	while(getchar() != '\n'){
		
	}

}
