#include <iostream>
#include <algorithm>
#include <cstring>

const int M = 1000 * 1000 * 1000 + 100;
int bino[201][201];

int skip = 3;

void calcBino() {
  std::memset(bino, 0, sizeof(bino));
  for (int i = 0; i <= 200; ++i) {
    bino[i][0] = bino[i][i] = 1;
    for(int j = 1; j < i; ++j)
      bino[i][j] = std::min(M, bino[i-1][j-1] + bino[i-1][j]);
  }
}

std::string kth(int n, int m, int skip) {
  if (n == 0)
    return std::string(m, 'o');
  if (skip < bino[n+m-1][n-1])
    return "-" + kth(n - 1, m, skip);
  return "o" + kth(n, m - 1, skip - bino[n+m-1][n-1]);
}

int main() {
  int n_case;
  std::cin >> n_case;

  calcBino();

  while (n_case > 0) {
    int n, m, k;
    std::cin >> n >> m >> k;

    std::cout << kth(n, m, k - 1) << std::endl;

    --n_case;
  }
  return 0;
}
