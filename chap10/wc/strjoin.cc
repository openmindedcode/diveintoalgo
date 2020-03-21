#include <iostream>
#include <vector>
#include <algorithm>

int calculateLoopCount(std::vector<int> &vec) {
  // sort descending order
  std::sort(vec.begin(), vec.end(), [](const int a, const int b) {
    return a > b;
      });

  int count = 0;
  while (vec.size() > 1) {
    // pop minimum two numbers and join them
    int num = vec.back();
    vec.pop_back();
    num += vec.back();
    vec.pop_back();
    count += num;

    // push to the joined number keeping descending order
    bool isPushed = false;
    for (auto it = vec.begin(); it != vec.end(); it++) {
      if (num > *it) {
        vec.insert(it, num);
        isPushed = true;
        break;
      }
    }
    if (!isPushed)
      vec.push_back(num);
  }
  return count;
}

int main() {
  int n_case = 0;
  std::cin >> n_case;
  while (n_case--) {
    int n_input = 0;
    std::cin >> n_input;

    std::vector<int> vec;
    for (int i = 0; i < n_input; ++i) {
      int input = 0;
      std::cin >> input;
      vec.push_back(input);
    }
    std::cout << calculateLoopCount(vec) << std::endl;
  }
  return 0;
}
