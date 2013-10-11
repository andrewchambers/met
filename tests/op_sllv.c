#include "test.h"

static inline unsigned int sllv(unsigned int a,unsigned int b) {
    unsigned int ret;
    asm("sllv %0,%1,%2\n" :"=r"(ret) :"r"(a) , "r"(b):  );
    return ret;
}


#define ASSERT(X) do { id++; if(!(X)) { outn(id); outs(""); return 1; } } while(0)



int main() {
    unsigned int id = 0;
    ASSERT(sllv(1,0) == 1);
    ASSERT(sllv(1,1) == 2);
    ASSERT(sllv(1,2) == 4);
    ASSERT(sllv(1,3) == 8);
    ASSERT(sllv(1,4) == 16);
    ASSERT(sllv(1,5) == 32);
    ASSERT(sllv(1,6) == 64);
    ASSERT(sllv(0xff0,4) == 0xff00);
    ASSERT(sllv(0xff0,32) == 0xff0);        
    return 0;    
}
