

#include "test.h"

static inline unsigned int add(unsigned int a,unsigned int b) {
    unsigned int ret;
    asm("add %0,%1,%2\n" :"=r"(ret) :"r"(a) , "r"(b):  );
    return ret;
}


#define ASSERT(X) do { id++; if(!(X)) { outn(id); outs(""); return 1; } } while(0)



int main() {
    unsigned int id = 0;
    ASSERT(add(0,0) == 0);
    ASSERT(add(0,0xff) == 0xff);
    ASSERT(add(1,0xff) == 0x100);
    ASSERT(add(0x123456,0x654321) == 7829367);
    ASSERT(add(0xffffffff,1) == 0);
    ASSERT(add(0xffffffff,0xffffffff) == 0xfffffffe);
    ASSERT(add(0xffffffff,0x1234567) == 0x1234566);
    
    return 0;    
}
