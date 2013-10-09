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

void clearERL() {
    unsigned int oldstatus,newstatus;
    asm("mfc0 %0, $12\n" :"=r"(oldstatus)::);
    //outs("status:");
    //outn(oldstatus);
    newstatus = oldstatus & ~(1 << CP0St_ERL);
    asm("mtc0 %0, $12\n" ::"r"(newstatus):);
}



int main()
{
    //set up 4k pages
    setPageMask(0);
    
    char data[4096*2];
    char data2[4096*2];
    
    unsigned int addr = (unsigned int)&data[0];
    unsigned int addr2 = (unsigned int)&data2[0];
    
    //make sure we are on a page boundary
    while(addr != (addr & 0xfffff000)){
        addr += 4;
    }
    
    unsigned int * pv = (unsigned int *)addr;
    *pv = 0xdeadbeef;
    
    unsigned int * px = (unsigned int *)(addr - 0x80000000);
    
    if(*px != 0xdeadbeef) {
        outs("direct access with erl set failed!");
        return 1;
    }
    
    
    writeTLBIndex(0);// select index 0 in tlb
    writeEntryHi(0,0); // we are mapping first and second onto the same physical as addr
    writeEntryLo(0,getPageNumber(addr - 0x80000000),2,1,1,1);
    writeEntryLo(1,getPageNumber(addr - 0x80000000),2,1,1,1);
    writeTLBWithIndex();    
    
    outs("configured tlb.");
    clearERL();
    
    
    if(*(unsigned int *)0 != 0xdeadbeef){
        outs("mapping of addr 2 failed!");
        outn(*(unsigned int *)0);
        outs("");
        return 1;
    }
    
    return 0;
}


