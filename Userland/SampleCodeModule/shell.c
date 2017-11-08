//#include "shell.h"
#include "syscalls.h"
#include "types.h"
#include "stdlib.h"
#include "stdio.h"
#include <graph.h>

void shell(){
	char* buffer[25*80];
	int i = 0;
	char c,d;
	char* user = "User: ";
	setTerminal(strlen(user));
	printf("%s\n", user);
	d = getchar();
	printf("%c\n", d);
	// settear el largo de como poronga vamos a llamar al chabon === User: 
	while(1) {
		if ((c = getchar()) != EOF) {
			if(c=='\b') {
				if(i != 0) {
					i--;
					buffer[i]=0;
					write(&c,1);
					backspace();
				}
			}
			else {
				if(c=='\n') {
					newline();
					write(&c,1);
					printf("%s\n", user);

					buffer[i]=0;
					parse(buffer);
					i=0;
					buffer[i]=0;
				}else {
					buffer[i]=c;
					i++;
					buffer[i]=0;
					write(&c,1);	
				}
			}
			//write(&c,1);
		}
	}
}

int parse(char* input) {
	if(strncmp("graph ",input,6) == 0) {
		int a=0,b=0,c=0;
		//no se que tan bien esta &(input[6])
		if(strncmp("line ",&(input[6]),5) == 0) {
			int j = 11;
			a = parseNum(&(input[j]), &j);
			j++;
			b = parseNum(&(input[j]), &j);
			graph_line(a,b);
		}
		else if(strncmp("cuadratic ",&(input[6]),10) == 0) {
			int j = 16;
			a = parseNum(&(input[j]), &j);
			j++;
			b = parseNum(&(input[j]), &j);
			j++;
			c = parseNum(&(input[j]), &j);
			graph_cuadratic(a,b,c);
		}
	}
}

int parseNum(char* input, int* p) {
	int a = 0;
	boolean neg = false;
	int j = *p;
	if(input[j] == '-') {
		neg = true;
		j++;
	}
	while(input[j]!=' ') {
		if(input[j]>='9' || input[j]<='0')
			return 0; //no se que hacer si pasan mal los argumentos
		a = 10*a + input[j] - '0';
		j++;
	}
	if(neg)
		a *= -1;
	*p = j; //no se si esto updatea p afuera
	return a;
}