

#include "test.h"

static inline unsigned int nor(unsigned int a,unsigned int b) {
    unsigned int ret;
    asm("nor %0,%1,%2\n" :"=r"(ret) :"r"(a) , "r"(b):  );
}


#define ASSERT(X) do { id++; if(!(X)) { outn(id); outs(""); return 1; } } while(0)



int main() {
    unsigned int id = 0;
    ASSERT(nor(0,0) == 0xffffffff);
    ASSERT(nor(0,0xff) == 0xffffff00);
    ASSERT(nor(1,0xff) == 0xffffff00);
    ASSERT(nor(0x123456,0x654321) == 0xff888888);
    ASSERT(nor(0xffffffff,1) == 0);
    ASSERT(nor(0xffffffff,0xffffffff) == 0);
    ASSERT(nor(0xffffffff,0x1234567) == 0);
    ASSERT(nor(0x10101010,0x01010101) == 0xeeeeeeee);
    ASSERT(nor(0x10101010,0xffffffff) == 0);
    ASSERT(nor(0x10101010,0x10101010) == 0xefefefef);
    return 0;
}
