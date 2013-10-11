

int main() {
    unsigned int a;
    #define XORI_TEST(V,C,ans) \
    a = V;\
    asm("xori %0,%1,"C"\n" \
    : "=r" (a) \
    : "r" (a) );\
     if(a != ans){ return 1; }
    XORI_TEST(0xffff0000,"0xffff",0xffffffff);
    XORI_TEST(0xffff00ff,"0x1",0xffff00fe);
    XORI_TEST(0xf0f0,"0xffff",0x0f0f);
    return 0;
}
