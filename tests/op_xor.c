

#include "test.h"

static inline unsigned int xor(unsigned int a,unsigned int b) {
    unsigned int ret;
    asm("xor %0,%1,%2\n" :"=r"(ret) :"r"(a) , "r"(b):  );
}


#define ASSERT(X) do { id++; if(!(X)) { outn(id); outs(""); return 1; } } while(0)



int main() {
    unsigned int id = 0;
    ASSERT(xor(0,0) == 0);
    ASSERT(xor(0,0xff) == 0xff);
    ASSERT(xor(1,0xff) == 0xfe);
    ASSERT(xor(0x123456,0x654321) == 7829367);
    ASSERT(xor(0xffffffff,1) == 0xfffffffe);
    ASSERT(xor(0xffffffff,0xffffffff) == 0);
    ASSERT(xor(0xffffffff,0x1234567) == 4275878552);
    ASSERT(xor(0x10101010,0x01010101) == 0x11111111);
    ASSERT(xor(0x10101010,0xffffffff) == 0xefefefef);
    ASSERT(xor(0x10101010,0x10101010) == 0);
    return 0;
}
