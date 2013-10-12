

#include "test.h"

static inline unsigned int subu(unsigned int a,unsigned int b) {
    unsigned int ret;
    asm("subu %0,%1,%2\n" :"=r"(ret) :"r"(a) , "r"(b):  );
    return ret;
}


#define ASSERT(X) do { id++; if(!(X)) { outn(id); outs(""); return 1; } } while(0)



int main() {
    unsigned int id = 0;
    ASSERT(subu(0,0) == 0);
    ASSERT(subu(10,5) == 5);
    ASSERT(subu(0xffffffff,0xffffffff) == 0);
    ASSERT(subu(0,1) == 0xffffffff);
    return 0;    
}
