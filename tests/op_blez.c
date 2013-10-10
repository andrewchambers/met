
int blez(int a,int * delaytaken) {
        
        int delay;   
        int branched;     
        
        asm( 
            ".set noreorder\n"
            "addi %1,$0,0\n"
            "addi %0,$0,1\n"
            "blez %2,__out\n"
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
            branched = blez(A,&delaytaken);\
            if (branched != TAKEN || delaytaken != DELAYTAKEN) {\
                return 1; \
            }\
    } while(0)
    
    BRANCHTEST(0,1,1);
    BRANCHTEST(2,0,1);
    BRANCHTEST(1,0,1);
    BRANCHTEST(0xffffffff,1,1);
    BRANCHTEST(-52,1,1);
    BRANCHTEST(52,0,1);
    
    
    return 0;
}
