#ifndef SYSCALLS_H_
#define SYSCALLS_H_

void read(char *buffer, unsigned int size);
void write(char *buffer, unsigned int size);
void time();
void setTerminal(unsigned long size);
void printGraphic(int color,int x,int y);
void getResolution(int *height,int * width);
#endif /* SYSCALLS_H_ */

