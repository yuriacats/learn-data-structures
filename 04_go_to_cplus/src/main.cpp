#include <stdio.h>
#include <stdlib.h>

/*
構造体：二つ以上のフィールドをまとめるもの
push
intが平均O(1)なので全体の処理としてO(n)くらいの計算量で済んでいる（maxはO(n)であることが知られている）
*/
const int N = 8000;
struct int_array {
  int max_size;
  int *data;
  int size;
  int *make_data(int data[], int size, int max_size) {
    int *new_data = new int[this->max_size];
    for (int i = 0; i < size; i++) {
      new_data[i] = data[i];
    }
    return new_data;
  }
  int_array(int data[], int size) {
    this->max_size = size * 2;
    this->size = size;
    this->data = make_data(data, size, max_size);
  }
  void push(int push_int) {
    if (size == max_size) {
      max_size *= 2;
      int *old_data = data;
      data = make_data(data, size, max_size);
      delete[] old_data;
    }
    data[size] = push_int;
    size++;
  }
  int max() {
    int max_int = 0;
    for (int i = 0; i < size; i++) {
      if (data[i] > max_int) {
        max_int = data[i];
      }
    }
    return max_int;
  }
  ~int_array() { delete[] data; }
};

int main() {
  int raw[5] = {1, 2, 14, 4, 5};
  // int_array myarray(raw, 5);
  int_array *myarray = new int_array(raw, 5);

  for (int i = 0; i < N / 2 - 1; i++) {
    myarray->push(12);
  }
  myarray->push(222);
  for (int i = 0; i < N / 2; i++) {
    myarray->push(12);
  }
  printf("%d\n", myarray->max());
  delete myarray;
  return 0;
}
