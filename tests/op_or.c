

#include "test.h"

static inline unsigned int or(unsigned int a,unsigned int b) {
    unsigned int ret;
    asm("or %0,%1,%2\n" :"=r"(ret) :"r"(a) , "r"(b):  );
}


#define ASSERT(X) do { id++; if(!(X)) { outn(id); outs(""); return 1; } } while(0)



int main() {
    unsigned int id = 0;
    ASSERT(or(0,0) == 0);
    ASSERT(or(0,0xff) == 0xff);
    ASSERT(or(1,0xff) == 0xff);
    ASSERT(or(0x123456,0x654321) == 7829367);
    ASSERT(or(0xffffffff,1) == 0xffffffff);
    ASSERT(or(0xffffffff,0xffffffff) == 0xffffffff);
    ASSERT(or(0xffffffff,0x1234567) == 0xffffffff);
    ASSERT(or(0x10101010,0x01010101) == 0x11111111);
    ASSERT(or(0x10101010,0xffffffff) == 0xffffffff);
    ASSERT(or(0x10101010,0x10101010) == 0x10101010);
    return 0;
}
