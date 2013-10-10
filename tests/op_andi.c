

int main() {
    unsigned int a;
    #define ANDI_TEST(V,C,ans) \
    a = V;\
    asm("andi %0,%1,"C"\n" \
    : "=r" (a) \
    : "r" (a) );\
     if(a != ans){ return 1; }
    ANDI_TEST(0xffff0000,"0xffff",0);
    ANDI_TEST(0xffff00ff,"1",1);
    ANDI_TEST(0x1,"0xffff",0x1);
    ANDI_TEST(0xffffffff,"1",0x1); 
    ANDI_TEST(0xffffffff,"0xffff",0x0000ffff);
    ANDI_TEST(0xffffffff,"32767",0x7fff);
    return 0;
}
