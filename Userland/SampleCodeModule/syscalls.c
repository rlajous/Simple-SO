//#include "syscalls.h"
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