

int main() {
    unsigned int a;
    #define ADDI_TEST(V,C,ans) \
    a = V;\
    asm("addi %0,%1,"C"\n" \
    : "=r" (a) \
    : "r" (a) );\
     if(a != ans){ return 1; }
    ADDI_TEST(0xffff0000,"0xffff",0xffff0000 - 1);
    ADDI_TEST(0xffff00ff,"0x1",0xffff0100);
    ADDI_TEST(0x1,"-1",0x0);
    return 0;
}
