#include <stdio.h>
#include <stdlib.h>

#include <iostream>
#include <vector>

const int64_t ring_size = 5;
struct ring_buffer_queue {
  std::vector<int64_t> buf;
  int64_t first_index = 0;
  int64_t next_index = 0;
  int64_t count = 0;

  ring_buffer_queue() : buf(ring_size + 1, 0) {}

  void enqueue(int64_t data) { ring_push_back(data); }
  int64_t dequeue() {
    if (count == 0) {
      throw "dequeu error ";
    }
    int64_t first = buf[first_index];
    first_index = (first_index + 1) % ring_size;
    count--;
    return first;
  }

 private:
  void ring_push_back(int64_t data) {
    if (count == ring_size) {
      throw "dequeu error ";
    }

    buf[next_index] = data;
    next_index = (next_index + 1) % ring_size;
    count++;
  }
};

int main() {
  ring_buffer_queue *test_queue = new ring_buffer_queue{};
  test_queue->enqueue(2);
  test_queue->enqueue(1);
  test_queue->enqueue(4);
  test_queue->enqueue(3);
  std::cout << test_queue->dequeue() << std::endl;
  test_queue->enqueue(5);
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
