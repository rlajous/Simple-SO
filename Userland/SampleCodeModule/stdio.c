#include "syscalls.h"
#include "stdlib.h"
#include "types.h"
#include <stdarg.h>

char buffer[25*80];

void readline(char* buff);

void putchar(char letter){
	write(&letter, 1);
}

char getchar(){
	char letter;
	do{
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
					break;
				case 'x':
					num = (int) va_arg(args, int);
					len = itoa(num, buffer, 16);
					index ++;
					break;
			}
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
	char* pc;
	int aux = 0, num = 0, len = 0,i = 1;
	readline(buffer);
	c = buffer[0];
	while(c != '\n' ){
		//aux = (char) va_arg(args, int);
		if(*format == '%'){
			switch(*(format+1)){
				case 'd':
					if((c >= '0' && c <= '9') || c == '-'){
						p = (int*) va_arg(args, int*);
						if(c == '-'){
							neg = true;				
						}

						do{
							
							aux = c - '0';
							
							num = (num*10) + aux;
							*p = num;
							c = buffer[i];
							i++;
						}while(c >= '0' && c <= '9');

						if(neg == true){
							*p *= -1;
						}

						format +=2;
						len++;
					}else {
						return len;
					}
					break;
				case 'c':
					if( (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c >= '0' && c <= '9')){
						pc = (char*) va_arg(args, char*);
						*pc = c;
						c = buffer[i]; 
						i++;
						format += 2;
						len++;
					}else{
						return len;
					}
					break;	

				case 's':
					if( (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c >= '0' && c <= '9')){
						pc = (char*) va_arg(args, char*);
						do {
							*(pc + aux) = c;
							aux++;
							c = buffer[i];
							i++;
						}while((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c >= '0' && c <= '9'));
						aux = 0;
						format += 2;
						len++;
					}else{
						return len;
					}
					break;
				}
		}else if(c == *format){
			c = buffer[i];
			i++;
			format++;
		}else{
			return len;
		
		}
	}
	return len;
}

void readline(char* buff){
	int j;
	for(j=0; (buff[j-1] != '\n') ; j++){
		do{
		buff[j] = getchar();
		printf("%c", buff[j]);
		if(buffer[j] == '\b'){
			buff[j] = 0;
			buff[j-1] = 0;
			j -= 2;
		}
		}while(buff[j] == -1);
	}
}