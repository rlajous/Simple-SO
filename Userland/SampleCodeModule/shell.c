//#include "shell.h"
#include "syscalls.h"
#include "types.h"
#include "stdlib.h"
#include "stdio.h"
#include <graph.h>

void shell(){
	char buffer[25*80];
	int i = 0;
	char c,d;
	char* user = "User: ";
	setTerminal(strlen(user));
	printf("\n");
	printf("%s\n", user);
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
					//printf("%s\n", user);

					buffer[i]=0;
					parse(buffer);
					//printf("%s", user);
					i=0;
					buffer[i]=0;
					printf("%s", user);
					printf("algo");
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

	
	int strcm = strncmp("graph ",input,6);
	//printf("%d\n",strncmp("clear",input,5));
	if (strncmp("cero",input,4)==0)
	{	
		printf("%d\n",4/0);
				
	}
	if (strncmp("clear",input,5)==0)
	{	
		clearScreen();
		printf("\n");
		printf("User: ");
	}
	
	if(strcm == 0) {
		int a=0,b=0,c=0;
		
		//no se que tan bien esta &(input[6])
		if(strncmp("line ",&(input[6]),5) == 0) {
			int j = 11;
			
			a = parseNum(input, &j);
			//graph line -2 -2
			j++;
			//printf("j:  %d  \n",j );

			b = parseNum(input, &j);
			//printf("j:  %d  \n",j );
			//printf("%d %d \n",a,b );
			clearScreen();
			graph_line(a,b);
			//printf("\n");
			//printf("User: ");
		}
		else if(strncmp("cuadratic ",&(input[6]),10) == 0) {
			int j = 16;
			a =parseNum(input, &j);
			j++;
			b =  parseNum(input, &j);
			j++;
			c = parseNum(input, &j);
			clearScreen();
			graph_cuadratic(a,b,c);
			printf("\n");
			//printf("User: ");
		}
	}
}

int parseNum(char* input, int * p) {
	int a = 0;
	boolean neg = false;
	int j = *p;
	//printf("j: %d\n", j);
	if(input[j] == '-') {
		neg = true;
		j++;
	}
	//printf("value: %d\n", input[j]);
	while(input[j]<='9' && input[j]>='0') {
	 //no se que hacer si pasan mal los argumentos
		a = 10*a + (input[j] - '0');
		//printf("a: %d\n", a);
		
		j++;
	}

	if(neg)
		a *= -1;
	*p = j; //no se si esto updatea p afuera
	//printf("value: %d\n", a);
	return a;
}