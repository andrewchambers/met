
void mult(int a,int b,int * outhi,int * outlo) {
    
    int lo;
    int hi;
    
    asm("mult %2,%3\n"
        "mfhi %0\n"
        "mflo %1\n": "=r" (hi) , "=r" (lo) :"r" (a), "r" (b):);
    
    *outhi = hi;
    *outlo = lo;
}

int main() {
    
    int hi;
    int lo;
    
    mult(15,0x88888889,&hi,&lo);
    
    if (hi != 0xfffffff9) {
        return 1;
    }
    
    if(lo != 7) {
        return 1;
    }    
        
    return 0;
}
