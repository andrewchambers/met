#include "test.h"

int main() {
    int out;
    asm("mfc0 %0,$15\n" : "=r" (out) ::);
    if (out != 0x00018000) {
        outn(out);
        return 1;
    }
    
    asm("mfc0 %0,$16\n" : "=r" (out) ::);
    
    
    if (out != 0x80008082) {
        outn(out);
        return 1;
    }
    
    return 0;
}
