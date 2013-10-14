#include "test.h"

#define CP0St_ERL   2
#define CP0St_EXL   1

void setCountReg(int count) {
    asm("mtc0 %0, $9\n" ::"r"(count):);
}

unsigned int getCountReg() {
    unsigned int ret;
    asm("mfc0 %0, $9\n" :"=r"(ret)::);
    return ret;
}

void setCompareReg(int comp) {
    asm("mtc0 %0, $11\n" ::"r"(comp):);
}

unsigned int getStatusReg() {
    unsigned int ret;
    asm("mfc0 %0, $12\n" :"=r"(ret)::);
    return ret;
}

void init() {
    unsigned int oldstatus,newstatus;
    
    setCompareReg(0x00100000);
    setCountReg(0);
    
    oldstatus = getStatusReg();
    newstatus = oldstatus & ~((1 << CP0St_ERL) | (1 << CP0St_EXL));    
    
    newstatus |= (1 << 15); //interrupt mask for timer
    newstatus |= 1; // interrupts enabled
    
    asm("mtc0 %0, $12\n" ::"r"(newstatus):);
    
}


int main() {
    
    init();
    
    while(1) {
        //wait for timer interrupt to occur.
        outn(getCountReg()); outs("");
        outs("status: "); outn(getStatusReg()); outs("");
    }   
    
    
    return 0;
}
