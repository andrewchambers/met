


int main() {
    
    int delaytaken = 0;
    asm( 
        
        ".set noreorder\n"
        "j __a\n"
        "nop\n"
        "nop\n"
        "__b:\n"
        "j __c\n"
        "nop\n"
        "nop\n"
        "__a:\n"
        "j __b\n"
        "nop\n"
        "__c:"
        "j __out\n"
        "addi %0,$0,1\n"
        ".set reorder\n"
        "__out:\n"
        : "=r" (delaytaken) ::);
    
    
    return !delaytaken;
}
