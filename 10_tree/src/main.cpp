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
  std::tuple<bool, tree_node *, tree_node *> search_node(tree_node *this_node,
                                                         int64_t value) {
    if (this_node->value == value) {
      return {true, this_node, nullptr};
    }
    if (this_node->left_node != nullptr) {
      auto [left_val, left_node, left_per_node] =
          search_node(this_node->left_node, value);
      if (left_val == true && left_per_node == nullptr) {
        return {left_val, left_node, this_node};
      }
      if (left_val == true && left_per_node != nullptr) {
        return {left_val, left_node, left_per_node};
      }
    }
    if (this_node->right_node != nullptr) {
      auto [left_val, left_node, left_per_node] =
          search_node(this_node->left_node, value);
      if (left_val == true && left_per_node == nullptr) {
        return {left_val, left_node, this_node};
      }
      if (left_val == true && left_per_node != nullptr) {
        return {left_val, left_node, left_per_node};
      }
    }
    return {false, nullptr, nullptr};
  }

  std::tuple<bool, tree_node *, tree_node *> node_serch(int64_t value) {
    tree_node this_node = *root_node;
    return search_node(&this_node, value);
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
  void deleteNodeWithAtMostOneChild(tree_node *child, tree_node *node_to_delete,
                                    tree_node *parent_node) {
    if (parent_node->left_node == node_to_delete) {
      parent_node->left_node = child;
    } else if (parent_node->right_node == node_to_delete) {
      parent_node->right_node = child;
    } else {
      throw "Invalid arguments provided to attach_children_node";
    }
    delete node_to_delete;
  }

 public:
  explicit tree(int64_t value) {
    root_node = new tree_node(value, nullptr, nullptr);
  }
  ~tree() { delete_node(root_node); }
  void insert(int64_t value) { insert_node(root_node, value); }
  bool serch(int64_t value) {
    auto [res, _, __] = node_serch(value);
    return res;
  }
  void delete_node(int64_t value) {
    auto [res, delete_target, delete_target_parent] = node_serch(value);
    if (res == false) {
      throw "not found";
    }

    printf("target_node:%ld\n", delete_target->value);
    // 葉の末端を削除するケース
    if (delete_target->left_node == nullptr &&
        delete_target->right_node == nullptr) {
      deleteNodeWithAtMostOneChild(nullptr, delete_target,
                                   delete_target_parent);
      return;
    }
    // 左右両方に子供が存在するケース
    if (delete_target->left_node != nullptr &&
        delete_target->right_node != nullptr) {
      auto [new_node, new_node_per] = get_max_node(delete_target->left_node);
      delete_target->value = new_node->value;
      if (new_node->left_node != nullptr) {
        deleteNodeWithAtMostOneChild(new_node->left_node, new_node,
                                     new_node_per);
      }
      deleteNodeWithAtMostOneChild(new_node->left_node, delete_target,
                                   delete_target_parent);
    }
    // 右側にのみ
    if (delete_target->right_node != nullptr) {
      printf("right node");
    }
    // 左側のみあるケース
    if (delete_target->left_node != nullptr) {
      printf("left node");
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
  my_tree.insert(5);
  my_tree.insert(15);
  my_tree.insert(3);
  my_tree.insert(7);
  my_tree.insert(12);
  my_tree.insert(18);
  my_tree.insert(5);

  // 探索
  bool found = my_tree.serch(7);
  // printf("7 is %s\n", found ? "found" : "not found");
  bool found2 = my_tree.serch(5);
  // printf("5 is %s\n", found2 ? "found" : "not found");

  // 削除
  my_tree.delete_node(5);
  found = my_tree.serch(5);
  // printf("5 is %s\n", found ? "found" : "not found");
  my_tree.print_nodes();
}
