#include "test.h"

int main(void)
{
  int s3 = 0, s5 = 0, s15 = 0;
  int i,ans;

  for (i = 0; i < 16; i++) {
    if (i % 3 == 0) {
      s3 += i;
    }
    if (i % 5 == 0) {
      s5 += i;
    }
    if (i % 15 == 0) {
      s15 += i;
    }
  }
  ans = s3 + s5 - s15;
  
  if (ans != 60) {
    return 1;
  }

  return 0;
}
  
