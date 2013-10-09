#include "test.h"

#define FAIL do { outs("\nFAILED:"); putchar(' '); putchar(' ');  outs(__func__); failed = 1;  } while(0)

int failed = 0;

void test_lui() {
	
	int v = 0;
	
	#define T(INIT,V,RES) \
	v = INIT; \
	asm("lui %0, " V "\n" : "=r"(v): "r"(v)); \
	if (v != RES) { \
		FAIL;\
	}
	
	T(0,"0xffff",0xffff0000)
	T(0xff,"0xffff",0xffff0000)
	T(0,"0x1000",0x10000000)
	T(0,"0x0",0x00000000)
	#undef T
	
}

void test_lw() {
	
	int x;
	int v[] = {0xdeadbeef,0x11223344,0x44332211};
	int * p = &v[1];
	
	asm("lw %0, 0(%1)\n" : "=r"(x) : "r"(p));
	
	if ( x != 0x11223344) {
		FAIL;
	}
	
	asm("lw %0, 4(%1)\n" : "=r"(x) : "r"(p));
	
	if ( x != 0x44332211) {
		FAIL;
	}
    
	asm("lw %0, -4(%1)\n" : "=r"(x) : "r"(p));
	
	if ( x != 0xdeadbeef) {
		FAIL;
	}
	
}

void test_lwl() {
	
	int x = 0;
	int v[] = {0x0,0x11223344,0x0};
	int * p = &v[1];
	
	x = 0;
	asm("lwl %0, 0(%1)\n" : "=r"(x) : "r"(p));
	
	if ( x != 0x11223344) {
	    outn(x);
		FAIL;
	}
	
	x = 0;
	asm("lwl %0, 1(%1)\n" : "=r"(x) : "r"(p));
	
	if ( x != 0x223344bc) {
		outn(x);
		FAIL;
	}
    
    x = 0;
	asm("lwl %0, 2(%1)\n" : "=r"(x) : "r"(p));
	
	if ( x != 0x3344ffbc) {
		outn(x);
		FAIL;
	}
	
	x = 0;
	asm("lwl %0, 3(%1)\n" : "=r"(x) : "r"(p));
	
	if ( x != 0x44ffffbc) {
		outn(x);
		FAIL;
	}
	
}

void test_lwr() {
	
	int x = 0;
	int v[] = {0x0,0x11223344,0x0};
	int * p = &v[1];
	
	x = 0;
	asm("lwr %0, 0(%1)\n" : "=r"(x) : "r"(p));
	
	if ( x != 0x82ffff11) {
	    outn(x);
		FAIL;
	}
	
	x = 0;
	asm("lwr %0, 1(%1)\n" : "=r"(x) : "r"(p));
	
	if ( x != 0x82ff1122) {
		outn(x);
		FAIL;
	}
    
    x = 0;
	asm("lwr %0, 2(%1)\n" : "=r"(x) : "r"(p));
	
	if ( x != 0x82112233) {
		outn(x);
		FAIL;
	}
	
	x = 0;
	asm("lwr %0, 3(%1)\n" : "=r"(x) : "r"(p));
	
	if ( x != 0x11223344) {
		outn(x);
		FAIL;
	}
	
}

void test_lb() {
	
	int x = 0;
	unsigned char v[] = {0x12,0xff,0x0};
	unsigned char * p = &v[1];
	
    
	asm("lb %0, 0(%1)\n" : "=r"(x) : "r"(p));
	
    
	if ( x != -1) {
		FAIL;
	}
	
	asm("lb %0, 1(%1)\n" : "=r"(x) : "r"(p));
	
    
	if ( x != 0) {
		FAIL;
	}
    
	asm("lb %0, -1(%1)\n" : "=r"(x) : "r"(p));
	
	if ( x != 0x12) {
		FAIL;
	}
	
}

void test_lbu() {
	
	int x = 0;
	unsigned char v[] = {0x12,0xff,0x0};
	unsigned char * p = &v[1];
	
    
	asm("lbu %0, 0(%1)\n" : "=r"(x) : "r"(p));
	
    
	if ( x != 0xff) {
		FAIL;
	}
	
	asm("lbu %0, 1(%1)\n" : "=r"(x) : "r"(p));
	
    
	if ( x != 0) {
		FAIL;
	}
    
	asm("lbu %0, -1(%1)\n" : "=r"(x) : "r"(p));
	
	if ( x != 0x12) {
		FAIL;
	}
	
}

void test_ori() {
	int v = 0;
	
	#define T(INIT,V,RES) \
	v = INIT; \
	asm("ori %0, " V "\n" : "=r"(v): "r"(v)); \
	if (v != RES) { \
		FAIL;\
	}
	
	T(0,"0xffff",0xffff)
	T(0xff,"0xffff",0xffff)
	T(0,"0x1000",0x1000)
	T(0xff,"0xff00",0xffff)
	#undef T
}


void test_sll() {
	
	int a;
	int v;
	
	#define T(A,SA,RES) \
	a = A;  \
	asm("sll %0, %1, " SA "\n" : "=r"(v): "r"(a)); \
	if (v != RES) { \
		FAIL;\
	}
	
	T(0,"0",0x0);
	T(0xfffffffe,"31",0x0);
	T(0xffffffff,"31",0x80000000);
	T(0x1,"2",4);

	#undef T
}

void test_srl() {
	
	int a;
	int v;
	
	#define T(A,SA,RES) \
	a = A;  \
	asm("srl %0, %1, " SA "\n" : "=r"(v): "r"(a)); \
	if (v != RES) { \
		FAIL;\
	}
	
	T(0,"0",0x0);
    T(4,"1",0x2);
	T(0xfffffffe,"31",0x1);
	T(0xffffffff,"31",0x00000001);
	T(0x1,"2",0);

	#undef T
}



void test_xor() {

    unsigned int a;
    unsigned int b;
    #define XOR_TEST(A,B,ans) \
    a = A; b = B;\
    asm("xor %0,%1,%2\n" \
    : "=r" (a) \
    : "r" (a) , "r" (b) );\
     if(a != ans){ FAIL; }
    XOR_TEST(0xffffffff,0xffff,0xffff0000);
    XOR_TEST(0xffff0000,0xffff,0xffffffff);
    XOR_TEST(0xffff000f,0xffff,0xfffffff0);
    XOR_TEST(0x0,0xffffffff,0xffffffff);
    XOR_TEST(0x0f0f0f0f,0xf0f0f0f0,0xffffffff);
    #undef XOR_TEST

}

void test_xori() {
    
    unsigned int a;
    #define XORI_TEST(V,C,ans) \
    a = V;\
    asm("xori %0,%1,"C"\n" \
    : "=r" (a) \
    : "r" (a) );\
     if(a != ans){ FAIL; }
    XORI_TEST(0xffffffff,"0xffff",0xffff0000);
    XORI_TEST(0xffff0000,"0xffff",0xffffffff);
    XORI_TEST(0xffff000f,"0xffff",0xfffffff0);
    #undef XORI_TEST
}

//XXX test overflow
void test_add(){
    unsigned int a;
    unsigned int b;
    #define ADD_TEST(A,B,ans) \
    a = A; b = B;\
    asm("add %0,%1,%2\n" \
    : "=r" (a) \
    : "r" (a) , "r" (b) );\
     if(a != ans){ FAIL; }
    ADD_TEST(0xffff0000,0xffff,0xffffffff);
    ADD_TEST(0xffff00ff,0x1,0xffff0100);
    #undef ADD_TEST
}

//XXX test overflow
void test_addi(){
    unsigned int a;
    #define ADDI_TEST(V,C,ans) \
    a = V;\
    asm("addi %0,%1,"C"\n" \
    : "=r" (a) \
    : "r" (a) );\
     if(a != ans){ FAIL; }
    ADDI_TEST(0xffff0000,"0xffff",0xffff0000 - 1);
    ADDI_TEST(0xffff00ff,"0x1",0xffff0100);
    ADDI_TEST(0x1,"-1",0x0);
    #undef ADDI_TEST
}

void test_addu(){
    unsigned int a;
    unsigned int b;
    #define ADDU_TEST(A,B,ans) \
    a = A; b = B;\
    asm("addu %0,%1,%2\n" \
    : "=r" (a) \
    : "r" (a) , "r" (b) );\
     if(a != ans){ FAIL; }
    ADDU_TEST(0xffff0000,0xffff,0xffffffff);
    ADDU_TEST(0xffff00ff,0x1,0xffff0100);
    #undef ADDU_TEST
}

void test_addiu(){
    unsigned int a;
    #define ADDIU_TEST(V,C,ans) \
    a = V;\
    asm("addiu %0,%1,"C"\n" \
    : "=r" (a) \
    : "r" (a) );\
     if(a != ans){ FAIL; }
    ADDIU_TEST(0xffff0000,"0xffff",0xffff0000 - 1);
    ADDIU_TEST(0xffff00ff,"0x1",0xffff0100);
    ADDIU_TEST(0x1,"-1",0x0);
    #undef ADDIU_TEST
}

void test_div() {
    unsigned int a;
    unsigned int b;
    #define DIV_TEST(A,B,ans,rem) \
    a = A; b = B;\
    asm("div %2,%3\n mflo %0\n mfhi %1\n" \
    : "=r" (a) , "=r" (b) \
    : "r" (a) , "r" (b) );\
     if(a != ans || b != rem ){ FAIL; outn(a); outs(""); outn(b); }
    DIV_TEST(0x1,0x1,1,0);
    DIV_TEST(5,2,2,1);
    DIV_TEST(-5,2,-2,-1);
    DIV_TEST(-5,-2,2,-1);
    DIV_TEST(5,-2,-2,1);
    DIV_TEST(50,-1,-50,0);
    DIV_TEST(100,2,50,0);
    #undef DIV_TEST
}

void test_divu() {
    unsigned int a;
    unsigned int b;
    #define DIVU_TEST(A,B,ans,rem) \
    a = A; b = B;\
    asm("divu %2,%3\n mflo %0\n mfhi %1\n" \
    : "=r" (a) , "=r" (b) \
    : "r" (a) , "r" (b) );\
     if(a != ans || b != rem ){ FAIL; }
    DIVU_TEST(0x1,0x1,1,0);
    DIVU_TEST(5,2,2,1);
    DIVU_TEST(0xffffffff,1,0xffffffff,0);
    DIVU_TEST(50,0xffffffff,0,50);
    DIVU_TEST(100,2,50,0);
    #undef DIVU_TEST
}


#define T(x) putchar('.'); x()

int main() {
    failed = 0;
	outs("---- starting opcode tests ----");
	T(test_add);
    T(test_addi);
    T(test_div);
    T(test_divu);
    T(test_lb);
    T(test_lbu);
    T(test_lui);
	T(test_lw);
	T(test_lwl);
	T(test_lwr);
	T(test_ori);
	T(test_sll);
    T(test_srl);
    T(test_xor);
    T(test_xori);
	outs("\n---- finished opcode tests ----");
	return failed;
}
