#include <stdio.h>
#include <stdlib.h>
/*
要件
1. ユーザーに標準入力で任意の数字(a)を書き込ませる
2. a回任意の数字を聞く(b_list)
3. 標準出力でb_listを表示する
*/

int main() {
  int N;
  printf("please set a number:");
  scanf("%d", &N);
  int *num_list = malloc(N * sizeof(int));
  if (num_list == NULL) {
    printf("Memory allocation faild");
  }
  for (int i = 0; i < N; i++) {
    printf("Please enter number %d:", i + 1);
    scanf("%d", &num_list[i]);
  }
  printf("You entered reverse:[");
  for (int i = N - 1; i >= 0; i--) {
    printf(" %d,", num_list[i]);
  }
  printf("]\n");
  free(num_list);
  return 0;
}
