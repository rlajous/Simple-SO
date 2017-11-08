#include "syscalls.h"
#include "stdlib.h"
#include "types.h"
#include <stdarg.h>

void putchar(char letter){
	write(&letter, 1);
}

char getchar(){
	char letter;
	read(&letter, 1);
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
	char c;
	boolean neg = false;
	int* p;
	int aux, num;
	c = getchar();
	while(c != '\n' ){
		//aux = (char) va_arg(args, int);
		if(format == '%'){
			switch(*(format+1)){
				case 'd':
					if(c >= '0' && c <= '9' || c == '-'){
						p = (int*) va_arg(args, int);
						if(c == '-'){
							neg = true;				
						}
						do{
							aux = atoi(c);
							num = (num*10) + aux;
							*p = num;
						}while(c >= '0' && c <= '9');
						if(neg == true){
							num = num - (2*num);
						}
						*p = num;
						format +=2;
					}else {
						return 0;
					}
					break;
				case 'c':
					if( (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')){}
					break;	

				case 's':
					break; 
			}
			format++;
		}else if(c == format){

		}
	}
	return 0;
}
