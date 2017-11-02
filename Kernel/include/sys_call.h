#ifndef SYSTEM_CALLS
#define SYSTEM_CALLS

void load_sys();
void sys_handler(int num,char*buffer,int size);

#endif