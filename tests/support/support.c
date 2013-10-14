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

/* helpers for writing exception handlers */

void writeJump(void * jmpTarget,void * jmpPc) {
    
    outs("writing jump handlers");
    unsigned int jTarget = (unsigned int) jmpTarget;
    unsigned int jPc = (unsigned int) jmpPc;
    
    unsigned int opcode = (1 << 27) | ((jTarget - jPc) & 0x3ffffff);
    *((unsigned int*) jmpPc) =  opcode;
    
    outn(*((unsigned int*) jmpPc));
    outs("");
}

extern void ehandler(); // type not so important, we just want its address

void setupExceptionHandler() {
    //Disabled totally
    unsigned int oldstatus,newstatus;
    asm("mfc0 %0, $12\n" :"=r"(oldstatus)::);
    newstatus = oldstatus & ~(1 << 22); //disable bev
    asm("mtc0 %0, $12\n" ::"r"(newstatus):);
    writeJump((void*)&ehandler,(void*)0x80000000);
    writeJump((void*)&ehandler,(void*)(0x80000000 + 0x180));
    writeJump((void*)&ehandler,(void*)(0x80000000 + 0x200));
    //writeJump((void*)&ehandler,(void*)0xBFC00200);
    //writeJump((void*)&ehandler,(void*)(0xBFC00200 + 0x180));
    //writeJump((void*)&ehandler,(void*)(0xBFC00200 + 0x200));
}



