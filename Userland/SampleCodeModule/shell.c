//#include "shell.h"
#include "syscalls.h"
#include "types.h"
#include "stdlib.h"
#include "stdio.h"
#include <graph.h>

void shell(){
    char buffer[25*80];
    int i = 0, ret = 0;
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
   				 newline2();
   				 buffer[i]=0;
   				 ret = parse(buffer);
   				 if(ret == 2)
   					 return;
   				 i=0;
   				 buffer[i]=0;
   				 printf("%s", user);
   				 printf("");
   			 }else {
   				 buffer[i]=c;
   				 i++;
   				 buffer[i]=0;
   				 write(&c,1);    
   			 }
   		 }
   	 }
    }
}

//retorna 0 si no hay error
int parse(char* input) {    
    if(strncmp("graph ",input,6) == 0) {
   	 clearScreen();
   	 printf("%s\n", "User: ");
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
   		 clearScreen();
   		 graph_cuadratic(a,b,c);
   		 return 0;
   	 }
   	 return -1;
    }
    if(strncmp(input, "echo ", 5) == 0) {
   	 newline();
   	 char* phrase = &(input[5]);
   	 write(phrase, strlen(phrase));
   	 newline2();
   	 return 0;
    }
    if(strcmp(input, "getTime") == 0) {
   	 time();
   	 return 0;
    }
    if(strcmp(input, "clear") == 0) {
   	  clearScreen();
   	  newline2();
   	  return 0;
    }
    if(strcmp(input, "help") == 0) {
   	 printHelp();
   	 newline2();
   	 return 0;
    }
    if(strcmp(input, "exit") == 0) {
   	 //return 1 es que termina shell()
   	 //pero no anda
   	 return 1;
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
    printf("\n");
    printf("graph (line|cuadratic) a b (c) - graphs a line (a*x + b) or a parabola (a*x*x + b*x + c)\n");
    printf("echo (message) - prints out the message\n");
    printf("getTime - prints the current time\n");
    printf("clear - clears the screen\n");
    printf("help - well.. you know what it does\n");
    printf("exit - exits the terminal");
}

void newline2() {
    newline();
    write("\n",1);
    printf("User: ");
}
