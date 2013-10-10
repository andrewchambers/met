int main() {
    unsigned int a;
    unsigned int b;
    #define DIVU_TEST(A,B,ans,rem) \
    a = A; b = B;\
    asm("divu %2,%3\n mflo %0\n mfhi %1\n" \
    : "=r" (a) , "=r" (b) \
    : "r" (a) , "r" (b) );\
     if(a != ans || b != rem ){ return 1; }
    DIVU_TEST(0x1,0x1,1,0);
    DIVU_TEST(5,2,2,1);
    DIVU_TEST(0xffffffff,1,0xffffffff,0);
    DIVU_TEST(50,0xffffffff,0,50);
    DIVU_TEST(100,2,50,0);
}
