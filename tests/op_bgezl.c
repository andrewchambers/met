

int bgezl(int a,int * delaytaken) {
        
        int delay;   
        int branched;     
        
        asm( 
            ".set noreorder\n"
            "addi %1,$0,0\n"
            "addi %0,$0,1\n"
            "bgezl %2,__out\n"
            "addi %1,$0,1\n"
            "addi %0,$0,0\n"
            ".set reorder\n"
            "__out:\n"
        : "&=r" (branched) , "&=r" (delay) : "r" (a)  :
        );
        
        *delaytaken = delay;
        return branched;
}


int main() {
    
    int delaytaken;
    int branched;
    
    #define BRANCHTEST(A,TAKEN,DELAYTAKEN) \
    do {    branched = 0 ; delaytaken = 0; \
            branched = bgezl(A,&delaytaken);\
            if (branched != TAKEN || delaytaken != DELAYTAKEN) {\
                return 1; \
            }\
    } while(0)
    
    BRANCHTEST(0,1,1);
    BRANCHTEST(0x7fffffff,1,1);
    BRANCHTEST(0x80000000,0,0);
    BRANCHTEST(0xffffffff,0,0);
    
    return 0;
}
