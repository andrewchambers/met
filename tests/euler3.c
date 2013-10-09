
int main(void)
{
  unsigned int n = 13195;
  unsigned int i;
  
  for (i = 2; i < n; i++) {
    while (n % i == 0) {
      n /= i;
    }
  }
  if(n != 29)
    return 1;

  return 0;
}
