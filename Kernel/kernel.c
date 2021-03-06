#include <stdint.h>
#include <string.h>
#include <lib.h>
#include <moduleLoader.h>
#include <RTC.h>
#include <naiveConsole.h>
#include <idtLoader.h>
#include <time.h>
#include <videoDriver.h>
#include <keyboardDriver.h>
#include "exeption.h"

extern uint8_t text;
extern uint8_t rodata;
extern uint8_t data;
extern uint8_t bss;
extern uint8_t endOfKernelBinary;
extern uint8_t endOfKernel;
//extern int mousescreen;

static const uint64_t PageSize = 0x1000;

static void * const sampleCodeModuleAddress = (void*)0x400000;
static void * const sampleDataModuleAddress = (void*)0x500000;

typedef int (*EntryPoint)();


void clearBSS(void * bssAddress, uint64_t bssSize)
{
	memset(bssAddress, 0, bssSize);
}

void * getStackBase()
{
	return (void*)(
		(uint64_t)&endOfKernel
		+ PageSize * 8				//The size of the stack itself, 32KiB
		- sizeof(uint64_t)			//Begin at the top of the stack
	);
}

void * initializeKernelBinary()
{
	char buffer[10];

	ncPrint("[x64BareBones]");
	ncNewline();

	ncPrint("CPU Vendor:");
	ncPrint(cpuVendor(buffer));
	ncNewline();

	ncPrint("[Loading modules]");
	ncNewline();
	void * moduleAddresses[] = {
		sampleCodeModuleAddress,
		sampleDataModuleAddress
	};

	loadModules(&endOfKernelBinary, moduleAddresses);
	ncPrint("[Done]");
	ncNewline();
	ncNewline();

	ncPrint("[Initializing kernel's binary]");
	ncNewline();

	clearBSS(&bss, &endOfKernel - &bss);

	ncPrint("  text: 0x");
	ncPrintHex((uint64_t)&text);
	ncNewline();
	ncPrint("  rodata: 0x");
	ncPrintHex((uint64_t)&rodata);
	ncNewline();
	ncPrint("  data: 0x");
	ncPrintHex((uint64_t)&data);
	ncNewline();
	ncPrint("  bss: 0x");
	ncPrintHex((uint64_t)&bss);
	ncNewline();

	ncPrint("[Done]");
	ncNewline();
	ncNewline();
	return getStackBase();
}


int main()
{	
	load_idt();
	load_sys();
	load_vDriver();
	load_exeptions();
	setFormat();
	char c;
	//clear();
	int a;

	((EntryPoint)sampleCodeModuleAddress)();
	//while (1);
	/*
	while(1){
		c=get_buffer();
		if (c!=-1)
		{	
			printChar(c);
			//printDec(1);
			//mousescreen++;
		}

	}
	*/
	/*
	int i = 90;
	int j = 10000000;
	while(i--) {
		while(j--);
		printChar('a');
		j = 10000000;
	}
	*/

	/*
	ncPrint("[Kernel Main]");
	ncNewline();
	ncPrint("  Sample code module at 0x");
	ncPrintHex((uint64_t)sampleCodeModuleAddress);
	ncNewline();
	ncPrint("  Calling the sample code module returned: ");
	ncPrintHex(((EntryPoint)sampleCodeModuleAddress)());
	ncNewline();
	ncNewline();

	ncPrint("  Sample data module at 0x");
	ncPrintHex((uint64_t)sampleDataModuleAddress);
	ncNewline();
	ncPrint("  Sample data module contents: ");
	ncPrint((char*)sampleDataModuleAddress);
	ncNewline();

	ncPrint("[Finished]");
	ncNewline();
	ncPrintColor("Arquitectura de las Computadoras",250);
	ncNewline();
	ncNewline();
	setFormat();
	printHs();
	*/
	/*
	printDec(ticks_elapsed());
	*/
	return 0;
}

void printHs(){
	int minutes=getMinutes();
	int seconds=getSeconds();
	int hours=getHours();
	ncPrintNumber(hours);
	ncPrint(":");
	ncPrintNumber(minutes);
	ncPrint(":");
	ncPrintNumber(seconds);
}
