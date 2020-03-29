#include <iostream>
#include <algorithm>
#include <cmath>
#include <utility>

const int INF = 987654321;
const double pi = 2.0 * acos(0);
int n;
double y[100], x[100], r[100];
std::pair<double, double> ranges[100];

void convertToRange() {
  for (int i = 0; i < n; ++i) {
    double loc = fmod(2 * pi + atan2(y[i], x[i]), 2 * pi);
    double range = 2.0 * asin(r[i] / 2.0 / 8.0);
    ranges[i] = std::make_pair(loc - range, loc + range);
  }

  std::sort(ranges, ranges+n);
}

int solveLinear(double begin, double end) {
  int used = 0, idx = 0;
  while (begin < end) {
    double maxCover = -1;
    while(idx < n && ranges[idx].first <= begin) {
      maxCover = std::max(maxCover, ranges[idx].second);
      ++idx;
    }
    if (maxCover <= begin)
      return INF;
    begin = maxCover;
    ++used;
  }
  return used;
}

int solveCircular() {
  int ret = INF;
  sort(ranges, ranges+n);

  for (int i = 0; i < n; ++i) {
    if(ranges[i].first <= 0 || ranges[i].second >= 2 * pi) {
      double begin = fmod(ranges[i].second, 2 * pi);
      double end = fmod(ranges[i].first + 2 * pi, 2 * pi);
      ret = std::min(ret, 1 + solveLinear(begin, end));
    }
  }
  return ret;
}

int main() {
  int n_case;
  std::cin >> n_case;
  while (n_case--) {
    std::cin >> n;
    for (int i = 0; i < n; ++i) {
      std::cin >> y[i] >> x[i] >> r[i];
    }
    convertToRange();
    int ret = solveCircular();
    if (ret == INF)
      std::cout << "IMPOSSIBLE" << std::endl;
    else
      std::cout << ret << std::endl;
  }

  return 0;
}
