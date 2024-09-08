#include <stdio.h>
#include <stdlib.h>

const long long int max_i = 40000;
const long long int max_j = 40000;
const long long int array_size = max_i*max_j;
int array[array_size];
int main() {
  long long int sum =0;
  for (int i=0; i<max_i;i++){
    for (int j=0; j<max_j;j++){
      array[i*max_j+j]=1;
    }
  }
  for (int i=0; i<max_i;i++){
    for (int j=0; j<max_j;j++){
      #sum += array[j*max_i+i];
      ## 平均25秒ほど実行にかかる 
      sum += array[i*max_j+j];
      ## 平均5秒ほど実行にかかる 
    }
  }

  printf("sum = %lld\n", sum);
  return 0;
}
