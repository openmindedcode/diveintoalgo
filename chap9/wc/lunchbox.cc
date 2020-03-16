#include <iostream>
#include <vector>
#include <cstring>
#include <algorithm>

class LunchBox {
 public:
  LunchBox() : m(0), e(0) {}
  int m;
  int e;
};

int calcMinimumTime(std::vector<LunchBox> vec, int n) {
  std::sort(vec.begin(), vec.end(), [] (LunchBox const& a, LunchBox const& b) {
    return a.e > b.e;
      });

  int heatingTime = 0;
  int leftEatingTime = 0;
  for (int i = 0; i < n; ++i) {
    heatingTime += vec[i].m;

    if (i > 0) {
      leftEatingTime -= vec[i].m;
      if (vec[i].e > leftEatingTime)
        leftEatingTime = vec[i].e;
    } else {
      leftEatingTime = vec[i].e;
    }
  }
  return heatingTime + leftEatingTime;
}

int main() {
  int n_case;
  std::cin >> n_case;

  while (n_case > 0) {
    int n_boxes;
    std::cin >> n_boxes;
    std::vector<LunchBox> vec;
    vec.resize(n_boxes);
    for (int i = 0; i < n_boxes; ++i) {
      std::cin >> vec[i].m;
    }
    for (int i = 0; i < n_boxes; ++i) {
      std::cin >> vec[i].e;
    }

    std::cout << calcMinimumTime(vec, n_boxes) << std::endl;
    --n_case;
  }
  return 0;
}
