#include <stdio.h>
#include <stdlib.h>

#include <tuple>
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
  void insert_node(tree_node *this_node, int64_t value) {
    if (this_node->value == value) {
      return;
    }
    if (this_node->value > value) {
      if (this_node->left_node == nullptr) {
        tree_node(value, nullptr, nullptr);
        return;
      }
      insert_node(this_node->left_node, value);
      return;
    }
    if (this_node->value < value) {
      if (this_node->right_node == nullptr) {
        tree_node(value, nullptr, nullptr);
        return;
      }
      insert_node(this_node->right_node, value);
      return;
    }
    // 来ないはずなのでErrorにしてもいいがreturnを書く
    return;
  }
  std::tuple<bool, tree_node *> search_node(tree_node *this_node,
                                            int64_t value) {
    if (this_node->value == value) {
      return {true, nullptr};
    }
    if (this_node->left_node == nullptr && this_node->right_node == nullptr) {
      return {false, nullptr};
    }
    if (this_node->value > value) {
      return {false, this_node->left_node};
    }
    if (this_node->value < value) {
      return {false, this_node->right_node};
    }
    throw "error";
  }

  std::tuple<bool, tree_node *> node_serch(int64_t value) {
    tree_node this_node = *root_node;
    while (true) {
      auto [res, next] = search_node(&this_node, value);
      if (res == true) {
        return {true, &this_node};
      }
      if (next == nullptr) {
        return {false, nullptr};
      }
      this_node = *next;
    }
  }
  std::tuple<tree_node *, tree_node *> get_max_node(tree_node *target_tree) {
    if (target_tree->right_node == nullptr) {
      return {target_tree, nullptr};
    }
    auto [res, next] = get_max_node(target_tree->right_node);
    if (res != nullptr && next == nullptr) {
      return {res, target_tree};
    }
    return {res, next};
  }

 public:
  explicit tree(int64_t value) { new tree_node(value, nullptr, nullptr); }
  ~tree() { delete_node(root_node); }
  void insert(int64_t value) { insert_node(root_node, value); }
  bool serch(int64_t value) {
    auto [res, _] = node_serch(value);
    return res;
  }
  void delete_node(int64_t value) {
    auto [res, target] = node_serch(value);
    if (res == false) {
      throw "not found";
    }
    if (target->left_node == nullptr && target->right_node == nullptr) {
      delete target;
    }
    auto [new_node, new_node_per] = get_max_node(target->left_node);
    target->value = new_node->value;
    new_node_per->left_node = new_node->left_node;
  }
};

int main() {}
