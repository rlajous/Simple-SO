#include <keyboardDriver.h>
#include <videoDriver.h>

#define TRUE 1
#define FALSE 0

#define BUFFER_SIZE 2000
#define LEFT 129
#define RIGHT 130
#define CAPS 131
#define SHIFT 132

unsigned char kbdus[128] =
{
    0,  27, '1', '2', '3', '4', '5', '6', '7', '8',	/* 9 */
  '9', '0', '-', '=', '\b',	/* Backspace */
  '\t',			/* Tab */
  'q', 'w', 'e', 'r',	/* 19 */
  't', 'y', 'u', 'i', 'o', 'p', '[', ']', '\n',	/* Enter key */
    0,			/* 29   - Control */
  'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';',	/* 39 */
 '\'', '`',   0,		/* Left shift */
 '\\', 'z', 'x', 'c', 'v', 'b', 'n',			/* 49 */
  'm', ',', '.', '/',   0,				/* Right shift */
  '*',
    0,	/* Alt */
  ' ',	/* Space bar */
    0,	/* Caps lock */
    0,	/* 59 - F1 key ... > */
    0,   0,   0,   0,   0,   0,   0,   0,
    0,	/* < ... F10 */
    0,	/* 69 - Num lock*/
    0,	/* Scroll Lock */
    0,	/* Home key */
    0,	/* Up Arrow */
    0,	/* Page Up */
  '-',
    LEFT,	/* Left Arrow */
    0,
    RIGHT,	/* Right Arrow */
  '+',
    0,	/* 79 - End key*/
    0,	/* Down Arrow */
    0,	/* Page Down */
    0,	/* Insert Key */
    0,	/* Delete Key */
    0,   0,   0,
    0,	/* F11 Key */
    0,	/* F12 Key */
    0,	/* All other keys are undefined */
};

static char buffer[BUFFER_SIZE];
static int index=0;
static int bufferindex=0;
static uint8_t ctrl=FALSE;
static uint8_t caps=FALSE;
static uint8_t shift=FALSE;
static uint8_t right=FALSE;
static uint8_t left=FALSE;
static uint8_t special=FALSE;

void keyboard_handler()
{

	//printChar('J');
    unsigned char scancode;

    /* Read from the keyboard's data buffer */
    scancode = get_key();

    /* If the top bit of the byte we read from the keyboard is
    *  set, that means that a key has just been released */
    if (scancode & 0x80)
    {
    		if(scancode==0x2A || scancode==0XAA||scancode==0x36 || scancode==0xB6){
        		shift=!shift;
				return;
			}

    }
    else
    {
        /* Here, a key was just pressed. Please note that if you
        *  hold a key down, you will get repeated key press
        *  interrupts. */

        /* Just to show you how this works, we simply translate
        *  the keyboard scancode into an ASCII value, and then
        *  display it to the screen. You can get creative and
        *  use some flags to see if a shift is pressed and use a
        *  different layout, or you can add another 128 entries
        *  to the above layout to correspond to 'shift' being
        *  held. If shift is held using the larger lookup table,
        *  you would add 128 to the scancode when you look for it */
        //putch(kbdus[scancode]);
        //putChar(kbdus[scancode]);
        //printChar(kbdus[scancode]);
    	char key=kbdus[scancode];
    	if (scancode==0x4B)
    	{
    		cursorLeft();
    		return;
    	}
    	if (scancode==0x4D)
    	{
    		cursorRight();
    		return;
    	}
    	
    	
        if(scancode==0x2A || scancode==0XAA||scancode==0x36 || scancode==0xB6){
        	shift=!shift;
			return;
		}else if(scancode==0x3A){
	        caps=!caps;
	        return;
		}
		if (shift || caps)
		{	
			if (key=='8')
			{
				buffer[bufferindex]='(';
				bufferindex=(bufferindex+1)%BUFFER_SIZE;
			}
			if (key=='9')
			{
				buffer[bufferindex]=')';
				bufferindex=(bufferindex+1)%BUFFER_SIZE;
			}
			if (key=='0')
			{
				buffer[bufferindex]='=';
				bufferindex=(bufferindex+1)%BUFFER_SIZE;
			}
			if (key=='7')
			{
				buffer[bufferindex]='/';
				bufferindex=(bufferindex+1)%BUFFER_SIZE;
			}if (key=='2')
			{
				buffer[bufferindex]='"';
				bufferindex=(bufferindex+1)%BUFFER_SIZE;
			}

			if (key<='z'&&key>='a')
			{
				buffer[bufferindex]=key-'a'+'A';
				bufferindex=(bufferindex+1)%BUFFER_SIZE;
			}
			if (key=='\n'||key=='\b')
            {
                buffer[bufferindex]=key;
                bufferindex=(bufferindex+1)%BUFFER_SIZE;
            }
		}else{
			buffer[bufferindex]=key;
			bufferindex=(bufferindex+1)%BUFFER_SIZE;
        }
       

    }
}

char get_buffer(){
    //printChar('a');
	if(index!=bufferindex){
		char aux=buffer[index];
		index=(index+1)%BUFFER_SIZE;
        //printChar('a');
        return aux;
    }
	return -1;
}
