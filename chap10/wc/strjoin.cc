#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

using PriorityQueue = std::priority_queue<int, std::vector<int>, std::greater<int>>;

int calculateLoopCount(PriorityQueue &queue) {
  int count = 0;
  while (queue.size() > 1) {
    int num = queue.top();
    queue.pop();
    num += queue.top();
    queue.pop();
    count += num;

    queue.push(num);
  }
  return count;
}

int main() {
  int n_case = 0;
  std::cin >> n_case;
  while (n_case--) {
    int n_input = 0;
    std::cin >> n_input;

    PriorityQueue queue;
    for (int i = 0; i < n_input; ++i) {
      int input = 0;
      std::cin >> input;
      queue.push(input);
    }
    std::cout << calculateLoopCount(queue) << std::endl;
  }
  return 0;
}
