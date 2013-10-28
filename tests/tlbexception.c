#include "test.h"

#define CP0St_ERL   2

unsigned int getPageNumber(unsigned int addr) {
    return addr >> 12;
}

void writeEntryHi(int vpn2, int asid)
{
    int entryHiVal = ((vpn2 << 13) & 0x7ffff) | (asid & 0xff);
    asm("mtc0 %0, $10"
        : 
        : "r" (entryHiVal)
        : 
    );
    return;
}

void writeEntryLo(int type, int pfn, int c, int d, int g, int v)
{
    int entryLoVal = ((pfn & 0xfffff) << 6) | ((c & 0x7) << 3) | ((d & 0x1) << 2) | ((v & 0x1) << 1) | (g & 0x1);
   
    if(type == 0)
    { 
        asm("mtc0 %0, $2"
            :
            : "r" (entryLoVal)
            :
           );
    }
    else if(type == 1)
    {
        asm("mtc0 %0, $3"
            :
            : "r" (entryLoVal)
            :
           );
    } 
    else
    {
        outs("Error, invalid entryLo type.");
    }
    return;
}

void writeTLBIndex(int index)
{
    asm("mtc0 %0, $0"
        :
        : "r" (index)
        :
        );
    return;
}

void writeTLBWithIndex()
{
   asm("tlbwi"
       :
       : 
       :
       );
}

void setPageMask(int pagemask) {
    asm("mtc0 %0, $5" ::"r"(pagemask):);
}

unsigned int getEPC(){
    unsigned int ret;
    asm("mfc0 %0, $14" :"=r" (ret)::);
    return ret;
}

void setEPC(unsigned int v){
    asm("mtc0 %0, $14" ::"r" (v):);
}


unsigned int getCause() {
    unsigned int ret;
    asm("mfc0 %0, $13" : "=r" (ret)::);
    return ret;
}

unsigned int getContext() {
    unsigned int ret;
    asm("mfc0 %0, $4" : "=r" (ret)::);
    return ret;
}

unsigned int getEntryHi() {
    unsigned int ret;
    asm("mfc0 %0, $10" : "=r" (ret)::);
    return ret;
}

unsigned int getBadVaddr() {
    unsigned int ret;
    asm("mfc0 %0, $8" : "=r" (ret)::);
    return ret;
}


void clearERL() {
    unsigned int oldstatus,newstatus;
    asm("mfc0 %0, $12\n" :"=r"(oldstatus)::);
    //outs("status:");
    //outn(oldstatus);
    newstatus = oldstatus & ~(1 << CP0St_ERL);
    asm("mtc0 %0, $12\n" ::"r"(newstatus):);
}

volatile int exceptionOccured = 0;

void exceptionHandler() {
        
    outs("exception handler");
    // let the exception repeat itself to test
    // that feature.
    if(!exceptionOccured) {
        exceptionOccured = 1;
        outs("first exception call");
        return;
    }
    
    if(getBadVaddr() != 0x70) {
        outs("bad Vaddr");
        exit(1);
    }

    if(((getCause() & 0x7c) >> 2) != 2) {
        outs("bad exception code");
        exit(1);
    }
    
    if(getContext()) {
        outs("bad context");
        return 1;
    }

    if(getEntryHi()) {
        outs("bad entry hi");
        return 1;
    }

    unsigned int epc = getEPC();
    setEPC(epc + 4); // skip the faulting instruction



    outs("done exception handler");
}


int main()
{
    outs("test start");
    registerExceptionHandler(&exceptionHandler);
    
    //set up 4k pages
    setPageMask(0);
    
    char data[4096*2];
    
    unsigned int addr = (unsigned int)&data[0];
    
    //make sure we are on a page boundary
    while(addr != (addr & 0xfffff000)){
        addr += 4;
    }
    
    unsigned int * pv = (unsigned int *)addr;
    *pv = 0xdeadbeef;
    
    unsigned int * px = (unsigned int *)(addr - 0xa0000000);
    
    outs("writing to address via direct access");
    if(*px != 0xdeadbeef) {
        outs("direct access with erl set failed!");
        return 1;
    }
    
    clearERL();
    
    if(exceptionOccured) {
        outs("premature exception");
        return 1;
    }
    
    int x = *(int*)0x70;
    
    if(!exceptionOccured) {
        return x|1;// lets fake use x so the compiler doesnt remove dead code
    }

    
    writeTLBIndex(0);// select index 0 in tlb
    writeEntryHi(0,0); // we are mapping first and second onto the same physical as addr
    writeEntryLo(0,getPageNumber(addr - 0xa0000000),2,1,1,1);
    writeEntryLo(1,getPageNumber(addr - 0xa0000000),2,1,1,1);
    writeTLBWithIndex();    
    
    outs("configured tlb.");
    
    
    if(*(unsigned int *)0 != 0xdeadbeef){
        outs("mapping of addr failed!");
        outn(*(unsigned int *)0);
        outs("");
        return 1;
    }
    
    outs("pass");
    return 0;
}


