#include <stdio.h>
#include <stdlib.h>
/*
構造体：二つ以上のフィールドをまとめるもの
push
intが平均O(1)なので全体の処理としてO(n)くらいの計算量で済んでいる（maxはO(n)であることが知られている）
*/
#define N 8000000
struct int_array {
  int max_size;
  int *data;
  int size;
};
int *int_malloc(int list_len) {
  int *m = malloc(list_len * sizeof(int));
  if (m == NULL) {
    exit(1);
  }
  return m;
}

struct int_array init_int_array(int data[], int size) {
  int maxsize = size * 2;
  struct int_array myarray;
  myarray.data = int_malloc(maxsize);
  for (int i = 0; i < size; i++) {
    myarray.data[i] = data[i];
  }
  myarray.size = size;
  myarray.max_size = maxsize;
  return myarray;
}

struct int_array *new_int_array(int data[], int size) {
  struct int_array result = init_int_array(data, size);
  struct int_array *res = malloc(sizeof(struct int_array));
  *res = result;
  return res;
}

void delete_int_array(struct int_array *data) {
  free(data->data);
  free(data);
}

void push_int_array(struct int_array *array, int pushed_int) {
  if (array->size == array->max_size) {
    array->max_size *= 2;
    int *newdata = int_malloc(array->max_size);
    for (int i = 0; i < array->size; i++) {
      newdata[i] = array->data[i];
    }
    free(array->data);
    array->data = newdata;
  }
  array->data[array->size] = pushed_int;
  array->size++;
}

int max(struct int_array *arr) {
  int max_int = 0;
  for (int i = 0; i < arr->size; i++) {
    if (arr->data[i] > max_int) {
      max_int = arr->data[i];
    }
  }
  return max_int;
}

int main() {
  int raw[5] = {1, 2, 14, 4, 5};
  struct int_array *myarray = new_int_array(raw, 5);

  for (int i = 0; i < N / 2 - 1; i++) {
    push_int_array(myarray, 12);
  }
  push_int_array(myarray, 222);
  for (int i = 0; i < N / 2; i++) {
    push_int_array(myarray, 12);
  }
  printf("%d\n", max(myarray));
  delete_int_array(myarray);
  return 0;
}
