int main() {
	
	int v = 0;
	
	#define T(INIT,V,RES) \
	v = INIT; \
	asm("lui %0, " V "\n" : "=r"(v): "r"(v)); \
	if (v != RES) { \
		return 1;\
	}
	
	T(0,"0xffff",0xffff0000)
	T(0xff,"0xffff",0xffff0000)
	T(0,"0x1000",0x10000000)
	T(0,"0x0",0x00000000)
	#undef T
	
}
