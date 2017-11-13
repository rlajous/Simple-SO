//#include "shell.h"
#include "syscalls.h"
#include "types.h"
#include "stdlib.h"
#include "stdio.h"
#include <graph.h>
#include "interrupt.h"

void invalid_op_code();

void shell(){
    char buffer[25*80];
    int i = 0, ret = 0;
    static int flag=1;
    char c,d;
    char* user = "User: ";
    setTerminal(strlen(user));
    //printf("\n");
    if (flag)
    {
    	printf("\n");
    	printHelp();
    	flag=0;
    }else{
    	newline2();
    }
    //printHelp();
    // settear el largo de como poronga vamos a llamar al chabon === User:
    while(1) {
   	 if ((c = getchar()) != EOF) {
   		 if(c=='\b') {
   			 if(i != 0) {
   				 i--;
   				 buffer[i]=0;
           putchar(c);
   				 backspace();
   			 }
   		 }
   		 else {
   			 if(c=='\n') {
   				 putchar(c);
   				 buffer[i]=0;
   				 ret = parse(buffer);
   				 if(ret == 1)
   					 return;
   				 i=0;
   				 buffer[i]=0;
   			 }else {
   				 buffer[i]=c;
   				 i++;
   				 buffer[i]=0;
   				 putchar(c);
   			 }
   		 }
   	 }
    }
}

//retorna 0 si no hay error
int parse(char* input) {    
    if(strncmp("graph ",input,6) == 0) {
   	 clearScreen();
   	 printf("\n");
   	 printf("%s", "User: ");
   	 int a=0,b=0,c=0;
   	 if(strncmp("line ",&(input[6]),5) == 0) {
   		 int j = 11;
   		 a = parseNum(input, &j);
   		 //graph line -2 -2
   		 j++;
   		 
   		 b = parseNum(input, &j);
   		 graph_line(a,b);
   		 return 0;
   	 }
   	 if(strncmp("cuadratic ",&(input[6]),10) == 0) {
   		 int j = 16;
   		 a =parseNum(input, &j);
   		 j++;
   		 b =  parseNum(input, &j);
   		 j++;
   		 c = parseNum(input, &j);
   		 //clearScreen();
   		 graph_cuadratic(a,b,c);
   		 return 0;
   	 }
   	 return -1;
    }else if(strncmp(input, "echo ", 5) == 0) {
		char* phrase = &(input[5]);
    	printf("%s\n", phrase);
    	printf("%s", "User: ");
   		return 0;
    }else if(strcmp(input, "getTime") == 0) {
    	int sec,min,hs,month,year=0;
   		time(&sec,&min,&hs,&month,&year);
   		printf("%d : %d : %d ",hs-3,min,sec);
   		newline2();
   		return 0;
    }else if(strcmp(input, "clear") == 0) {
   	  clearScreen();
   	  newline2();
   	  return 0;
    }else if(strcmp(input, "help") == 0) {
   	 printHelp();
   	 return 0;
    }else if(strcmp(input, "exit") == 0) {
   	 //return 1 es que termina shell()
   	 //pero no anda
   	 return 1;
    }else if(strcmp(input, "cero") == 0) {
   		printf("%d\n",4/0);
    	//invalid_op_code();
    }else if(strcmp(input, "invalidOpCode") == 0) {
   		//printf("%d\n",4/0);
    	invalid_op_code();
    }else{
    	printf("Wrong command\n");
    	printf("%s", "User: ");
    }
    return -1;
}

int parseNum(char* input, int * p) {
    int a = 0;
    boolean neg = false;
    int j = *p;
    if(input[j] == '-') {
   	 neg = true;
   	 j++;
    }
    while(input[j]<='9' && input[j]>='0') {
     //no se que hacer si pasan mal los argumentos
   	 a = 10*a + (input[j] - '0');
   	 j++;
    }

    if(neg)
   	 a *= -1;
    *p = j; //no se si esto updatea p afuera
    //printf("value: %d\n", a);
    return a;
}

void printHelp() {
    printf("graph (line|cuadratic) a b (c) - graphs a line (a*x + b) or a parabola (a*x*x + b*x + c)\n");
    printf("echo (message) - prints out the message\n");
    printf("getTime - prints the current time in argentina\n");
    printf("clear - clears the screen\n");
    printf("cero - makes an divition by cero exeption\n");
    printf("invalidOpCode - makes an invalid operation exeption\n");
    printf("help - display available commands\n");
    printf("exit - exits the terminal");
    newline2();
}

void newline2() {
    //newline();
    //write("\n",1);
    printf("\nUser: ");
}
