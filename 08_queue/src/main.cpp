#include <stdio.h>
#include <stdlib.h>

#include <iostream>
#include <vector>

struct ring_buffer_queue {
  std::vector<int64_t> buf = {0, 0, 0, 0, 0};
  int64_t now_first_point = 0;
  int64_t max_point = 0;
  int64_t ring_size = 5;

  void enqueue(int64_t data) { ring_push_back(data); }
  int64_t dequeue() {
    if (buf.size() == 0) {
      throw "error";
    }
    if (now_first_point > ring_size - 1) {
      now_first_point = 0;
    }
    int64_t first = buf[now_first_point];
    now_first_point++;
    return first;
  }
  void ring_push_back(int64_t data) {
    if (max_point > ring_size - 1) {
      max_point = 0;
    }
    buf[max_point] = data;
    max_point++;
  }
};

int main() {
  ring_buffer_queue *test_queue = new ring_buffer_queue{};
  test_queue->enqueue(2);
  test_queue->enqueue(1);
  test_queue->enqueue(4);
  test_queue->enqueue(3);
  std::cout << test_queue->dequeue() << std::endl;
  std::cout << test_queue->dequeue() << std::endl;
  std::cout << test_queue->dequeue() << std::endl;
  std::cout << test_queue->dequeue() << std::endl;
  test_queue->enqueue(5);
  test_queue->enqueue(6);
  test_queue->enqueue(7);
  test_queue->enqueue(8);
  std::cout << test_queue->dequeue() << std::endl;
  std::cout << test_queue->dequeue() << std::endl;
  std::cout << test_queue->dequeue() << std::endl;
  std::cout << test_queue->dequeue() << std::endl;
  std::cout << test_queue->dequeue() << std::endl;
  return 0;
}
