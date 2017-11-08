#include "syscalls.h"
#include <interrupt.h>

void int_80h(unsigned long rdi, unsigned long rsi, unsigned long rdx, unsigned long rcx, unsigned long r8, unsigned long r9);

void read(char *buffer, unsigned int size) {
     int_80h(2, (unsigned long) buffer, (unsigned long)size,0,0,0);
}
void write(char *buffer, unsigned int size) {
     int_80h(1, (unsigned long) buffer, (unsigned long)size,0,0,0);
}
void time(int sec,int min,int hs,int mont,int year) {
     int_80h(4, (unsigned long) sec,(unsigned long) min,(unsigned long) hs, (unsigned long) mont,(unsigned long) year);
}
void setTerminal(unsigned long size){
	int_80h(3,size,0, 0, 0,  0);
}
void printGraphic(int color,int x,int y) {
     int_80h(5, (unsigned long) color, (unsigned long)x,(unsigned long)y,0,0);
}
void getResolution(int *height,int * width) {
     int_80h(6, (unsigned long) height, (unsigned long)width,0,0,0);
}
void backspace() {
     int_80h(7,0,0,0,0,0);
}
void newline() {
     int_80h(8,0,0,0,0,0);
}
void clearScreen() {
     int_80h(0,0,0,0,0,0);
}