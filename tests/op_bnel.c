

int bnel(int a, int b,int * delaytaken) {
        
        int delay;   
        int branched;     
        
        asm( 
            ".set noreorder\n"
            "addi %1,$0,0\n"
            "addi %0,$0,1\n"
            "bnel %2,%3,__out\n"
            "addi %1,$0,1\n"
            "addi %0,$0,0\n"
            ".set reorder\n"
            "__out:\n"
        : "&=r" (branched) , "&=r" (delay) : "r" (a) , "r" (b) :
        );
        
        *delaytaken = delay;
        return branched;
}


int main() {
    
    int delaytaken;
    int branched;
    
    #define BRANCHTEST(A,B,TAKEN,DELAYTAKEN) \
    do {    branched = 0 ; delaytaken = 0; \
            branched = bnel(A,B,&delaytaken);\
            if (branched != TAKEN || delaytaken != DELAYTAKEN) {\
                return 1; \
            }\
    } while(0)
    
    BRANCHTEST(0,0,0,0);
    BRANCHTEST(2,2,0,0);
    BRANCHTEST(0,1,1,1);
    BRANCHTEST(1,0,1,1);
    BRANCHTEST(1,1,0,0);
    BRANCHTEST(0,0xffffffff,1,1);
    BRANCHTEST(0xffff,0xffff,0,0);
    BRANCHTEST(0xffffffff,0,1,1);
    
    
    return 0;
}
