#include <stdio.h>
#include <stdlib.h>

#include <vector>
#define DEFAULT_N 100

long long int readN() {
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
  int_linked_list_node(int data) {
    this->data = data;
    next_node = nullptr;
  }
  ~int_linked_list_node() { delete next_node; }
};

struct int_linked_list {
  int length;
  int_linked_list_node *first_node;
  int_linked_list_node *last_node;
  int_linked_list(std::vector<int> data) {
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
  void firstappend(int data) { first_node = new int_linked_list_node(data); }
  void prepend(int data) {
    if (this->first_node == nullptr) {
      firstappend(data);
    }
    int_linked_list_node *new_first_node = new int_linked_list_node(data);
    new_first_node->next_node = this->first_node;
    this->first_node = new_first_node;
    length++;
  }
  void append(int data) {
    if (this->first_node == nullptr) {
      firstappend(data);
    }
    int_linked_list_node *new_last_node = new int_linked_list_node(data);
    this->last_node->next_node = new_last_node;
    this->last_node = new_last_node;
    length++;
  }
  void delete_last() {
    int_linked_list_node *last_node = first_node;
    while (last_node->next_node->next_node != nullptr) {
      last_node = last_node->next_node;
    }
    delete last_node->next_node;
    last_node->next_node = nullptr;
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
  if (l == nullptr) {
    printf("\n");
    return;
  }
  while (true) {
    printf("%d, ", l->data);
    if (l->next_node == nullptr) {
      break;
    }
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
  long long int N = readN();
  int_linked_list *test = new int_linked_list(std::vector<int>{});
  // print_int_linked_list(test);
  for (long long int i = 0; i < N; i++) {
    test->prepend(i);
  }
  // print_int_linked_list(test);
  delete test;
}
void linked_list_append_test_function() {
  long long int N = readN();
  int_linked_list *test = new int_linked_list(std::vector<int>{});
  // print_int_linked_list(test);
  for (long long int i = 0; i < N; i++) {
    test->append(i);
  }
  // print_int_linked_list(test);
  delete test;
}

void vector_prepend_test_function() {
  long long int N = readN();
  std::vector<long long int> *test = new std::vector<long long int>{};
  for (long long int i = 0; i < N; i++) {
    std::vector<long long int> *new_vector = new std::vector<long long int>{i};
    for (int it = 0; it < test->size(); it++) {
      new_vector->push_back((*test)[it]);
    }
    delete test;
    test = new_vector;
  }
  delete test;
}

int main() {
  vector_prepend_test_function();
  //  linked_list_prepend_test_function();
  // linked_list_append_test_function();

  return 0;
}
