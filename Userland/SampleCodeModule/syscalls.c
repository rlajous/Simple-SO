//#include "syscalls.h"

void _int80h(unsigned long rdi, unsigned long rsi, unsigned long rdx, unsigned long rcx, unsigned long r8, unsigned long r9);

void read(char *buffer, unsigned int size) {
     _int80h(2, (uint64_t) buffer, (uint64_t)size,0,0,0);
}
void write(char *buffer, unsigned int size) {
     _int80h(1, (uint64_t) buffer, (uint64_t)size,0,0,0);
}
void time(int sec,int min,int hs,int mont,int year) {
     _int80h(4, (uint64_t) sec,(uint64_t) min,(uint64_t) hs, (uint64_t) mont,(uint64_t) year);
}