#include "plat.h"

int putchar (int c) {
	write_serial(c);
}

void outs(const char * s) {
	while(*s){
		putchar(*s++);
	}
	putchar('\n');
}

void outn(unsigned int n) {
    int i = 0;
    char * hexchars = "0123456789abcdef";
    char output[9];
    output[8] = 0;
    while (i != 8) {
        output[7-i] = hexchars[n % 16];
        n = n / 16;
        i++;
    }
    
    char * o = &output[0];
    
    while(*o){
        putchar(*o);
        o++;
    }
}

void exit(int) __attribute__ ((noreturn));

void exit(int x) {
    outs("exit:");
    outn(x);
    power_down();
}


void abort(void) __attribute__ ((noreturn));

void abort(void) {
    outs("abort.");
    power_down();
}

/* helpers for writing interrupt handlers */

void writeJump(void * jmpTarget,void * jmpPc) {
    unsigned int jTarget = (unsigned int) jmpTarget;
    unsigned int jPc = (unsigned int) jmpPc;
    
    unsigned int opcode = (1 << 27) | ((jTarget - jPc) & 0x3ffffff);
    *((unsigned int*) jmpPc) = opcode;
}



