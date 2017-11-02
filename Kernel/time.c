#include <time.h>
#include <videoDriver.h>

static unsigned long ticks = 0;

void timer_handler() {
	ticks++;
	if ((ticks_elapsed()%9)==0)
	{
		blink();
	}
}

int ticks_elapsed() {
	return ticks;
}

int seconds_elapsed() {
	return ticks / 18;
}
