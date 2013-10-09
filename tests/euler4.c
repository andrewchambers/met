#include "test.h"

static int is_palindromic(unsigned int n);

int main(void)
{
  if(! is_palindromic(1001)) {
    return 1;
  }
  
  if(! is_palindromic(1234321)) {
    return 1;
  }
  
  if(is_palindromic(1000)) {
    return 1;
  }
  
  return 0;
}

int is_palindromic(unsigned int n)
{
  unsigned int reversed = 0, t = n;

  while (t) {
    reversed = 10*reversed + (t % 10);
    t /= 10;
  }
  return reversed == n;
}
