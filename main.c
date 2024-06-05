#include <stdio.h>
#include <math.h>

int main(void){
  long n;

  printf("\n%s", "Enter a number to check if it is prime:");
  scanf("%ld", &n);

  if(n == 2 || n == 3){
    printf("%ld is prime.", n);
    return 0;
  }

  if(n <= 1){
    printf("%ld is NOT prime.", n);
    return 0;
  }

  if(n % 2 == 0){
    puts("Hit prime divisor 2.");
    printf("%ld is NOT prime.", n);
    return 0;
  }

  if(n % 3 == 0){
    puts("Hit prime divisor 3.");
    printf("%ld is NOT prime.", n);
    return 0;
  }

  long floor_sqrt_n = (long)sqrt(n);

  for(long i = 5; i <= floor_sqrt_n; i += 6){
    if(n % i == 0){
      printf("Hit prime divisor %ld\n", i);
      printf("%ld is NOT prime", n);
      return 0;
    }
    if(n % (i + 2) == 0){
      printf("Hit prime divisor %ld\n", i + 2);
      printf("%ld is NOT prime", n);
      return 0;
    }
  }

  printf("%ld is prime.", n);

  return 0;
}
