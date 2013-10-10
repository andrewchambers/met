#include "test.h"

#define UART_BASE (0xa0000000 + 0x14000000 + 0x03f8) //fixed memory map + ISA base + serial base


#define POWER_BASE (0xa0000000 + 0x1fbf0000) //fixed memory map + power


static inline unsigned char inb(unsigned int base, unsigned int offset) {
	return (*(unsigned volatile char *)(base +offset*1));
}

static inline void outb(unsigned int base, unsigned int offset,unsigned int v) {
	*(unsigned volatile char *)(base +offset*1) = (unsigned char)v;
}

static inline int is_transmit_empty() {
   return inb(UART_BASE,5) & 0x20;
}
 
void write_serial(char a) {
   while (is_transmit_empty() == 0);
   outb(UART_BASE,0,a);
}

void power_down() {
	outb(POWER_BASE,4,42);
	while(1);
}


int main();

void plat_main() {
    setupExceptionHandler();
	if (main() != 0 ) {
	    outs("Test: " CURTEST " FAIL");
	} else {
	    outs("Test: " CURTEST " PASS");
	}
	power_down();
}
