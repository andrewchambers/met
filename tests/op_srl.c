#include "test.h"




int main() {
    unsigned int a,b;
    
    #define TEST(A,SHAMT,EXPECTED) \
        do { \
            a = A;\
            asm("srl %0,%1,"SHAMT : "=r"(b) : "r" (a)  ); \
            if (b != (EXPECTED)) {return 1;} \
        } while(0)
    
    TEST(0,"0",0);
    TEST(0,"10",0);
    TEST(1,"0",1);
    TEST(1,"1",0);
    TEST(2,"1",1);
    TEST(0xff0,"4",0xff);
    TEST(0x80000000,"4",0x08000000);
        
    return 0;    
}
