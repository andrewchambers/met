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

void setStatusReg(int status) {
    asm("mtc0 %0, $12\n" ::"r"(status):);
}


volatile int timerInterruptOccured = 0;

volatile int timerInterruptCounter = 0;


void timerIntHandler() {

    if(timerInterruptCounter >= 1) {
        timerInterruptOccured = 1;
        unsigned int oldstatus;
        
        oldstatus = getStatusReg();
        
        setCompareReg(0x10); // now timer interrupts should be frequent
                             // in case something is broken
        //clear interrupt enable
        setStatusReg(oldstatus & (~1));
        
        
    } else {
        //test ignoring the first timer interrupt and having it reraised
        timerInterruptCounter += 1;
    }
    
    
    
}


void init() {
    
    
    registerExceptionHandler(&timerIntHandler);    
    
    unsigned int oldstatus,newstatus;
    
    setCompareReg(0x00100000);
    setCountReg(0);
    
    oldstatus = getStatusReg();
    newstatus = oldstatus & ~((1 << CP0St_ERL) | (1 << CP0St_EXL));    
    
    newstatus |= (1 << 15); //interrupt mask for timer
    newstatus |= 1; // interrupts enabled
    
    setStatusReg(newstatus);
    
}





int main() {
    
    init();
    
    while(1) {
        if(timerInterruptOccured) {
            break;
        }
    }
    
    timerInterruptOccured = 0;
    
    int i;
    for(i = 0; i < 1000; i+= 1) {
        if(timerInterruptOccured) {
            return 1;
        }
    }
    
    
    return 0;
}
