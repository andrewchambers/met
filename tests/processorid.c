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
    
    asm("mfc0 %0,$16, 1\n" : "=r" (out) ::);
    
    
    if (out != 0x9e190c8a && out != 0x1e190c8a) {
        outn(out);
        return 1;
    }
    
    asm("mfc0 %0,$13\n" : "=r" (out) ::);
    
    if (out != 0 ) {
        outn(out);
        return 1;
    }    
    
    return 0;
}
