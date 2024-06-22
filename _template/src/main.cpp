#include <stdio.h>
#include <stdlib.h>

#define DEFAULT_N 100

long long int readN() {
  char *envN = getenv("N");
  if (envN) {
    return atoll(envN);
  } else {
    return DEFAULT_N;
  }
}

int main() {
  long long int N = readN();

  printf("%lld\n", N);
  long long int sum = 0;
  for (long long int i = 0; i < N; i++) {
    sum += i;
  }

  printf("sum = %lld\n", sum);
  return 0;
}
