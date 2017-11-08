#ifndef SYSCALLS_H_
#define SYSCALLS_H_

void read(char *buffer, unsigned int size);
void write(char *buffer, unsigned int size);
void time(int sec,int min,int hs,int mont,int year);
void setTerminal(unsigned long size);
void printGraphic(int color,int x,int y);
void getResolution(int *height,int * width);
#endif /* SYSCALLS_H_ */

