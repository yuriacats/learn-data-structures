#include <stdio.h>
#include <stdlib.h>

#include <iostream>
#include <string>
#include <tuple>
#include <vector>
#define DEFAULT_N 100
const int64_t empty = -1;
const int64_t deleted = -2;
const int64_t used = 1;

struct hash_entry {
  int64_t key;
  int64_t value;
  int64_t member_flag;
  hash_entry() : key(-1), value(0), member_flag(empty) {}
};
struct hash_get_result {
  int64_t index;
  int64_t value;
};

class hash_table {
  int64_t table_size;
  std::vector<hash_entry> table;
  int64_t hash_calculate(int64_t key) { return key % table_size; }
  int64_t hash_recalculate(int64_t hash) { return (hash + 1) % table_size; }
  void insert_entry(int64_t key, int64_t value, int64_t hash) {
    table[hash].key = key;
    table[hash].value = value;
    table[hash].member_flag = used;
  }

 public:
  hash_table(int64_t n = DEFAULT_N) : table_size(n), table(n) {
    if (n <= 0) {
      throw "table size must be greater than 0";
    }
  }
  void insert(int64_t key, int64_t value) {
    hash_get_result target = get(key);
    if (target.index != -1) {
      insert_entry(key, value, target.index);
      return;
    }
    int64_t hash = hash_calculate(key);
    if (table[hash].member_flag == empty ||
        table[hash].member_flag == deleted) {
      insert_entry(key, value, hash);
      return;
    }
    while (table[hash].member_flag == used) {
      hash = hash_recalculate(hash);
    }
    insert_entry(key, value, hash);
    return;
  }
  hash_get_result get(int64_t key) {
    int64_t hash = hash_calculate(key);
    while (table[hash].member_flag != empty) {
      if (table[hash].key == key) {
        return {hash, table[hash].value};
      }
      hash = hash_recalculate(hash);
    }
    return {-1, 0};
  }
  void remove(int64_t key) {
    hash_get_result result = get(key);
    if (result.index == -1) {
      throw "key not found";
    }
    table[result.index].member_flag = deleted;
    table[result.index].key = -1;
    table[result.index].value = 0;
  }
};

void repl() {
  std::cout << "| list"
               "| insert <key> <value>"
               "| get <key>"
               "| remove <key>"
               "| exit"
            << std::endl;

  hash_table table(100);

  while (true) {
    std::cout << ">" << std::flush;
    std::string command;
    std::cin >> command;
    if (command == "exit") {
      break;
    } else if (command == "list") {
      std::cout << "todo" << std::endl;
    } else if (command == "insert") {
      int64_t key;
      int64_t value;
      std::cin >> key >> value;
      table.insert(key, value);
    } else if (command == "get") {
      int64_t key;
      std::cin >> key;
      hash_get_result result = table.get(key);
      if (result.index == -1) {
        std::cout << "key not found" << std::endl;
      } else {
        std::cout << "key: " << key << " value: " << result.value << std::endl;
      }
    } else if (command == "remove") {
      int64_t key;
      std::cin >> key;
      table.remove(key);
    } else {
      std::cout << "invalid command" << std::endl;
    }
  }
}

void test_performance(int table_size, int data_size, int query_count) {
  hash_table table(table_size);

  // initiate
  std::vector<int64_t> keys(data_size);
  for (int i = 0; i < data_size; i++) {
    keys[i] = rand();
  }

  for (int i = 0; i < data_size; i++) {
    table.insert(keys[i], i);
  }

  // query
  for (int i = 0; i < query_count; i++) {
    int64_t key = keys[query_count % data_size];

    table.get(key);
  }
}

int main(int argc, char const *argv[]) {
  int table_size = atoi(argv[1]);
  int data_size = atoi(argv[2]);
  int query_count = atoi(argv[3]);

  test_performance(table_size, data_size, query_count);
  return 0;
}
