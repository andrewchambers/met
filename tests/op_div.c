
int main() {
    unsigned int a;
    unsigned int b;
    #define DIV_TEST(A,B,ans,rem) \
    a = A; b = B;\
    asm("div %2,%3\n mflo %0\n mfhi %1\n" \
    : "=r" (a) , "=r" (b) \
    : "r" (a) , "r" (b) );\
     if(a != ans || b != rem ){ return 1; }
    DIV_TEST(0x1,0x1,1,0);
    DIV_TEST(5,2,2,1);
    DIV_TEST(-5,2,-2,-1);
    DIV_TEST(-5,-2,2,-1);
    DIV_TEST(5,-2,-2,1);
    DIV_TEST(50,-1,-50,0);
    DIV_TEST(100,2,50,0);
    #undef DIV_TEST
}
