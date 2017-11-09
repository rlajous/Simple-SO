#ifndef KERNEL
#define KERNEL

void clearBSS(void * bssAddress, uint64_t bssSize);
void * getStackBase();
void * initializeKernelBinary();
void printHs();

#endif