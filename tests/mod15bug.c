#include "test.h"

int main(void)
{
  int x = 0;
  int i;

  for (i = 0; i < 16; i++) {
    if(i == 15) {
        if (i % 15 != 0) {
          return 1;
        }
    }
  }

  return 0;
}
  
