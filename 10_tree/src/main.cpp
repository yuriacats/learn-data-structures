#include <stdio.h>
#include <stdlib.h>

#include <cstdio>
#include <tuple>
#define DEFAULT_N 100

struct tree_node {
  int64_t value;
  tree_node *left_node;
  tree_node *right_node;

  explicit tree_node(int64_t value, tree_node *left, tree_node *right) {
    this->value = value;
    this->left_node = left;
    this->right_node = right;
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
        this_node->left_node = new tree_node(value, nullptr, nullptr);
        return;
      }
      insert_node(this_node->left_node, value);
      return;
    }
    if (this_node->value < value) {
      if (this_node->right_node == nullptr) {
        this_node->right_node = new tree_node(value, nullptr, nullptr);
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
    if (this_node == nullptr) {
      return {false, nullptr};
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
  // ここもデバック用のプリントを残しているので最後に消す
  std::tuple<tree_node *, tree_node *> get_max_node(tree_node *target_tree) {
    printf("max_node(first):%ld\n", target_tree->value);
    if (target_tree->right_node == nullptr) {
      printf("max_node(tt):%ld\n", target_tree->value);
      return {target_tree, nullptr};
    }
    auto [res, next] = get_max_node(target_tree->right_node);
    if (res != nullptr && next == nullptr) {
      printf("max_node(erro):%ld\n", res->value);
      return {res, target_tree};
    }
    return {res, next};
  }
  void print_node(tree_node *this_node) {
    if (this_node == nullptr) {
      return;
    }
    print_node(this_node->left_node);
    printf("%ld\n", this_node->value);
    print_node(this_node->right_node);
  }

 public:
  explicit tree(int64_t value) {
    root_node = new tree_node(value, nullptr, nullptr);
  }
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
    if (target->left_node != nullptr) {
      // TODOこの辺りのケースの処理ができてないのでやる
      auto [new_node, new_node_per] = get_max_node(target->left_node);
      printf("max_node:%ld\n", new_node->value);
      printf("max_node(check):%ld\n", new_node_per->right_node->value);
      printf("test6\n");
      target->value = new_node->value;

      printf("test7\n");
      if (new_node->left_node != nullptr) {
        new_node_per->left_node = new_node->left_node;
      }
      printf("test8\n");
      delete new_node;
      printf("test9\n");
      new_node_per->right_node = nullptr;
      printf("test10\n");
    }
  }
  void print_nodes() { print_node(root_node); }
};

int main() {
  tree my_tree(8);
  my_tree.print_nodes();
  my_tree.insert(5);
  my_tree.insert(15);
  my_tree.insert(3);
  my_tree.insert(7);
  my_tree.insert(12);
  my_tree.insert(18);

  // 探索
  bool found = my_tree.serch(7);
  printf("7 is %s\n", found ? "found" : "not found");
  bool found2 = my_tree.serch(5);
  printf("5 is %s\n", found2 ? "found" : "not found");

  // 削除
  my_tree.delete_node(5);
  found = my_tree.serch(5);
  printf("5 is %s\n", found ? "found" : "not found");
}
