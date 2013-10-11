

#include "test.h"

static inline unsigned int and(unsigned int a,unsigned int b) {
    unsigned int ret;
    asm("and %0,%1,%2\n" :"=r"(ret) :"r"(a) , "r"(b):  );
    return ret;
}


#define ASSERT(X) do { id++; if(!(X)) { outn(id); outs(""); return 1; } } while(0)



int main() {
    unsigned int id = 0;
    ASSERT(and(0,0) == 0);
    ASSERT(and(0,0xff) == 0);
    ASSERT(and(1,0xff) == 0x1);
    ASSERT(and(0x123456,0x654321) == 0);
    ASSERT(and(0xffffffff,1) == 1);
    ASSERT(and(0xffffffff,0xffffffff) == 0xffffffff);
    ASSERT(and(0xffffffff,0x1234567) == 0x1234567);
    ASSERT(and(0x10101010,0x01010101) == 0);
    ASSERT(and(0x10101010,0xffffffff) == 0x10101010);
    ASSERT(and(0x10101010,0x10101010) == 0x10101010);
    return 0;    
}
