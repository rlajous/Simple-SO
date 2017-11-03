//#include "syscalls.h"

void _int80h(unsigned long rdi, unsigned long rsi, unsigned long rcx, unsigned long r8, unsigned long r9);

void read(void *buffer, unsigned int size) {
    return _int80h(2, (uint64_t) buffer, size,0,0);
}
void write(void *buffer, unsigned int size) {
    return _int80h(1, (uint64_t) buffer, size,0,0);
}
