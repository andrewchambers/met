

int main() {
    unsigned int a;
    #define ADDIU_TEST(V,C,ans) \
    a = V;\
    asm("addiu %0,%1,"C"\n" \
    : "=r" (a) \
    : "r" (a) );\
     if(a != ans){ return 1; }
    ADDIU_TEST(0xffff0000,"0xffff",0xffff0000 - 1);
    ADDIU_TEST(0xffff00ff,"0x1",0xffff0100);
    ADDIU_TEST(0x1,"-1",0x0);
    ADDIU_TEST(0xffffffff,"1",0x0); //overflow
    
    return 0;
}
