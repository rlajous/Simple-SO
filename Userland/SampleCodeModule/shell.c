//#include "shell.h"
#include "syscalls.h"
#include "stdlib.h"
#include <graph.h>

void shell(){
	char* input;
	int i = 0;
	while(input[i] != -1) {
		read(&(input+i), 1)
		i++;
	}
	if(strncmp("graph ",input,6) == 0) {
		int a=0,b=0,c=0;
		//no se que tan bien esta &(input[6])
		if(strncmp("line ",&(input[6]),5) == 0) {
			int j = 11;
			a = parseNum(&(input[j]), &j);
			if(j<0)
				return;
			j++;
			b = parseNum(&(input[j]), &j);
			if(j<0)
				return;
			graph_line(a,b);
		}
		else if(strncmp("cuadratic ",&(input[6]),10) == 0) {
			int j = 16;
			a = parseNum(&(input[j]), &j);
			if(j<0)
				return;
			j++;
			b = parseNum(&(input[j]), &j);
			if(j<0)
				return;
			j++;
			c = parseNum(&(input[j]), &j);
			if(j<0)
				return;
			graph_cuadratic(a,b,c);
		}
	}
	
}

int parseNum(char* input, int* p) {
	int a = 0;
	bool neg = false;
	int j = *p;
	if(input[j] == '-') {
		neg = true;
		j++;
	}
	while(input[j]!=' ') {
		if(input[j]>'9' || input[j]<'0')
			return 0; //no se que hacer si pasan mal los argumentos
		a = 10*a + input[j];
		j++;
	}
	if(neg)
		a *= -1;
	*p = j; //no se si esto updatea p afuera
	return a;
}