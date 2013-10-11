#include "test.h"




int main() {
    unsigned int a,b;
    
    #define TEST(A,SHAMT,EXPECTED) \
        do { \
            a = A;\
            asm("sll %0,%1,"SHAMT : "=r"(b) : "r" (a)  ); \
            if (b != (EXPECTED)) {return 1;} \
        } while(0)
    
    TEST(0,"0",0);
    TEST(0,"10",0);
    TEST(1,"0",1);
    TEST(1,"1",2);
    TEST(1,"2",4);
    TEST(1,"3",8);
    TEST(1,"4",16);
    TEST(1,"5",32);
    TEST(1,"6",64);
    TEST(1,"31",0x80000000);
    TEST(0xff0,"4",0xff00);
        
    return 0;    
}
