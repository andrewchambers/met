#include "test.h"




int main() {
    unsigned int a,b;
    
    #define TEST(A,SHAMT,EXPECTED) \
        do { \
            a = A;\
            asm("sra %0,%1,"SHAMT : "=r"(b) : "r" (a)  ); \
            if (b != (EXPECTED)) {return 1;} \
        } while(0)
    
    TEST(0,"0",0);
    TEST(2,"0",2);
    TEST(4,"1",2);
    TEST(0xfff00000,"4",0xffff0000);
    TEST(0x7ff00000,"4",0x07ff0000);
    
        
    return 0;    
}
