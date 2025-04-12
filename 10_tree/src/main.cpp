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
  void delete_tree(tree_node *this_node) {
    if (this_node->left_node != nullptr) {
      delete_tree(this_node->left_node);
    }
    if (this_node->right_node != nullptr) {
      delete_tree(this_node->right_node);
    }
    delete this_node;
  }
  void insert_node(tree_node *this_node, int64_t value) {
    if (this_node->value == value) {
      return;
    }
    if (value < this_node->value) {
      if (this_node->left_node == nullptr) {
        this_node->left_node = new tree_node(value, nullptr, nullptr);
        return;
      }
      insert_node(this_node->left_node, value);
      return;
    }
    if (value > this_node->value) {
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
  // 返り値は（見つかったか, 見つかった対象のnodeのポインタ,
  // 見つかった対象を指し示しているポインタ
  std::tuple<bool, tree_node *, tree_node **> search_node(
      tree_node *this_node, int64_t value, tree_node **pointer_to_this_node) {
    if (this_node->value == value) {
      return {true, this_node, pointer_to_this_node};
    }
    if (this_node->left_node != nullptr) {
      auto [found_in_left_tree, left_node, pointer_to_found_node] =
          search_node(this_node->left_node, value, &this_node->left_node);
      if (found_in_left_tree) {
        return {found_in_left_tree, left_node, pointer_to_found_node};
      }
    }
    if (this_node->right_node != nullptr) {
      auto [found_in_right_tree, right_node, pointer_to_found_node] =
          search_node(this_node->right_node, value, &this_node->right_node);
      if (found_in_right_tree) {
        return {found_in_right_tree, right_node, pointer_to_found_node};
      }
    }
    return {false, nullptr, nullptr};
  }

  std::tuple<bool, tree_node *, tree_node **> search_node(int64_t value) {
    return search_node(root_node, value, &root_node);
  }
  // 帰り値は　（最大値のnodeポインタ, そのnodeの親ポインタ）
  // ただし、引数のnode自身が最大値であるときは(最大値のnodeポインタ,
  // nullptr)を返す
  std::tuple<tree_node *, tree_node **> get_max_node(
      tree_node *target_tree, tree_node **pointer_to_target_tree) {
    if (target_tree->right_node == nullptr) {
      return {target_tree, pointer_to_target_tree};
    }
    return get_max_node(target_tree->right_node, &(target_tree->right_node));
  }
  void print_node(tree_node *this_node) {
    if (this_node == nullptr) {
      printf("null");
      return;
    }
    printf("{\"value\": ");
    printf("\"%ld\"", this_node->value);
    printf(", \"left\": ");
    print_node(this_node->left_node);
    printf(", \"right\": ");
    print_node(this_node->right_node);
    printf("}");
  }
  void deleteNodeWithAtMostOneChild(tree_node *node_to_delete,
                                    tree_node **pointer_to_node_to_delete) {
    if (node_to_delete == nullptr) {
      throw "nullptr has been passed to the tree_node in the function";
    }
    if (pointer_to_node_to_delete == nullptr) {
      throw "nullptr has been passed to the tree_node in the function";
    }
    // gcc系の独自拡張文法。使えない場合は第二項に一項と同じ値を入れること
    auto child = node_to_delete->left_node ?: node_to_delete->right_node;
    *pointer_to_node_to_delete = child;
    delete node_to_delete;
  }

 public:
  explicit tree(int64_t value) {
    root_node = new tree_node(value, nullptr, nullptr);
  }
  ~tree() { delete_tree(root_node); }
  void insert(int64_t value) { insert_node(root_node, value); }
  bool search(int64_t value) {
    auto [found, _, __] = search_node(value);
    return found;
  }
  void delete_node(int64_t value) {
    auto [is_target_found, delete_target, pointer_to_delete_target] =
        search_node(value);
    if (!is_target_found) {
      throw "not found";
    }
    // 葉の末端を削除するケース
    if (delete_target->left_node == nullptr &&
        delete_target->right_node == nullptr) {
      deleteNodeWithAtMostOneChild(delete_target, pointer_to_delete_target);
    } else if (delete_target->left_node == nullptr &&
               delete_target->right_node != nullptr) {
      deleteNodeWithAtMostOneChild(delete_target, pointer_to_delete_target);
    } else if (delete_target->left_node != nullptr &&
               delete_target->right_node == nullptr) {
      deleteNodeWithAtMostOneChild(delete_target, pointer_to_delete_target);
    } else {
      auto [left_max_node, left_max_node_parent] =
          get_max_node(delete_target->left_node, &delete_target->left_node);
      delete_target->value = left_max_node->value;
      deleteNodeWithAtMostOneChild(left_max_node, left_max_node_parent);
    }
  }
  void print_nodes() {
    printf("'");
    print_node(root_node);
    printf("'\n");
  }
};

int main() {
  tree my_tree(8);
  my_tree.insert(15);
  my_tree.insert(5);
  my_tree.insert(3);
  my_tree.insert(7);
  my_tree.insert(12);
  my_tree.insert(18);
  my_tree.insert(5);

  // 探索
  bool found = my_tree.search(7);
  printf("7 is %s\n", found ? "found" : "not found");
  bool found2 = my_tree.search(5);
  printf("5 is %s\n", found2 ? "found" : "not found");

  // 削除
  my_tree.delete_node(8);
  found = my_tree.search(5);
  printf("5 is %s\n", found ? "found" : "not found");
  my_tree.print_nodes();
  my_tree.insert(5);
  found = my_tree.search(5);
  printf("5 is %s\n", found ? "found" : "not found");
}
