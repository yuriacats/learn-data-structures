#include <stdio.h>
#include <stdlib.h>

#define DEFAULT_N 100

struct tree_node {
  int64_t value;
  tree_node *left_node;
  tree_node *right_node;

  tree_node(int64_t value, tree_node *left, tree_node *right) {
    value = value;
    left_node = left;
    right_node = right;
  }
};

class tree {
  tree_node *root_node;
  void delete_node(tree_node *this_node) {
    if (this_node->left_node != nullptr) {
      delete_node(this_node->left_node);
    }
    if (this_node->right_node != nullptr) {
      delete_node(this_node->right_node);
    }
    delete this_node;
  }

 public:
  explicit tree(int64_t value) { new tree_node(value, nullptr, nullptr); }
  ~tree() { delete_node(root_node); }
};

int main() { return 0; }
