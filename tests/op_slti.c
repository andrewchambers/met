#include "test.h"




int main() {
    unsigned int a,b;
    
    #define TEST(A,B,EXPECTED) \
        do { \
            a = A;\
            asm("slti %0,%1,"B : "=r"(b) : "r" (a)  ); \
            if (b != (EXPECTED)) {return 1;} \
        } while(0)
    
    TEST(0,"0",0);
    TEST(-1,"0",1);
    TEST(-1,"-1",0);
    TEST(10,"5",0);
    TEST(5,"10",1);
    TEST(10,"-1",0);
    return 0;
}
