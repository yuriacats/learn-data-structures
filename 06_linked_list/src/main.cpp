#include <stdio.h>
#include <stdlib.h>

#include <vector>
#define DEFAULT_N 100

int64_t readN() {
  char *envN = getenv("N");
  if (envN) {
    return atoll(envN);
  } else {
    return DEFAULT_N;
  }
}

struct int_linked_list_node {
  int_linked_list_node *next_node;
  int data;
  explicit int_linked_list_node(int64_t data) {
    this->data = data;
    next_node = nullptr;
  }
  ~int_linked_list_node() { delete next_node; }
};

struct int_linked_list {
  int64_t length;
  int_linked_list_node *first_node;
  int_linked_list_node *last_node;
  explicit int_linked_list(std::vector<int64_t> data) {
    this->length = data.size();
    if (data.size() == 0) {
      this->first_node = nullptr;
      return;
    }
    this->first_node = new int_linked_list_node(data[0]);
    last_node = this->first_node;
    for (int i = 1; i < data.size(); i++) {
      int_linked_list_node *node = new int_linked_list_node(data[i]);
      last_node->next_node = node;
      last_node = node;
    }
  }
  ~int_linked_list() { delete first_node; }
  void firstappend(int data) {
    first_node = new int_linked_list_node(data);
    last_node = first_node;
    length = 1;
  }

  void prepend(int data) {
    if (!(this->first_node)) {
      firstappend(data);
      return;
    }
    int_linked_list_node *new_first_node = new int_linked_list_node(data);
    new_first_node->next_node = this->first_node;
    this->first_node = new_first_node;
    length++;
  }
  void append(int data) {
    if (this->first_node == nullptr) {
      firstappend(data);
      return;
    }
    int_linked_list_node *new_last_node = new int_linked_list_node(data);
    this->last_node->next_node = new_last_node;
    this->last_node = new_last_node;
    length++;
  }
  void delete_last() {
    int_linked_list_node *target_node = first_node;
    while (target_node->next_node != last_node) {
      target_node = target_node->next_node;
    }
    delete last_node;
    target_node->next_node = nullptr;
    last_node = target_node;
    length--;
  }
  void delete_first() {
    int_linked_list_node *new_first_node = this->first_node->next_node;
    first_node->next_node = nullptr;
    delete first_node;
    this->first_node = new_first_node;
    length--;
  }
};

void print_int_linked_list(int_linked_list *list) {
  int_linked_list_node *l = list->first_node;
  while (l) {
    printf("%d, ", l->data);
    l = l->next_node;
  }
  printf("\n");
}
void print_int_linked_list(std::vector<int> *list) {
  for (int i = 0; i < list->size() - 1; i++) {
    printf("%d ,", (*list)[i]);
  }
  printf("\n");
}
void linked_list_prepend_test_function() {
  int64_t N = readN();
  int_linked_list *test = new int_linked_list(std::vector<int64_t>{});
  // print_int_linked_list(test);
  for (int64_t i = 0; i < N; i++) {
    test->prepend(i);
  }
  // print_int_linked_list(test);
  delete test;
}
void linked_list_append_test_function() {
  int64_t N = readN();
  int_linked_list *test = new int_linked_list(std::vector<int64_t>{});
  // print_int_linked_list(test);
  for (int64_t i = 0; i < N; i++) {
    test->append(i);
  }
  print_int_linked_list(test);
  delete test;
}

void vector_prepend_test_function() {
  int64_t N = readN();
  std::vector<int64_t> *test = new std::vector<int64_t>{};
  for (int64_t i = 0; i < N; i++) {
    std::vector<int64_t> *new_vector = new std::vector<int64_t>{i};
    for (int it = 0; it < test->size(); it++) {
      new_vector->push_back((*test)[it]);
    }
    delete test;
    test = new_vector;
  }
  delete test;
}

int main() {
  // vector_prepend_test_function();
  //   linked_list_prepend_test_function();
  linked_list_append_test_function();

  return 0;
}
