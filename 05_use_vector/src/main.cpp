#include <stdio.h>
#include <stdlib.h>

#include <algorithm>
#include <vector>
/*
構造体：二つ以上のフィールドをまとめるもの
push
intが平均O(1)なので全体の処理としてO(n)くらいの計算量で済んでいる（maxはO(n)であることが知られている）
*/
const int N = 8000;

int main() {
  int raw[5] = {1, 2, 14, 4, 5};
  // std::vector<int> *myarray = new std::vector<int>(raw[5]);
  std::vector<int> myarray_raw(raw[5]);
  std::vector<int> *myarray = &myarray_raw;

  for (int i = 0; i < N / 2 - 1; i++) {
    myarray->push_back(12);
  }
  myarray->push_back(222);
  for (int i = 0; i < N / 2; i++) {
    myarray->push_back(12);
  }
  printf("%d\n", *std::max_element(myarray->begin(), myarray->end()));
  // delete myarray;
  return 0;
}
