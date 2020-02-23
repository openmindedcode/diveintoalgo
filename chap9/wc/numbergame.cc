#include <iostream>

const int EMPTY = -987654321;
int n, board[50];
int cache[50][50];

int play(int left, int right) {
  if (left > right)
    return 0;

  int& ret = cache[left][right];
  if (ret != EMPTY)
    return ret;

  ret = std::max(board[left] - play(left + 1, right),
      board[right] - play(left, right - 1));

  if (right - left + 1 >= 2) {
    ret = std::max(ret, -play(left + 2, right));
    ret = std::max(ret, -play(left, right - 2));
  }

  return ret;
}

int main() {
  int n_case;
  std::cin >> n_case;

  while (n_case) {
    for (int i = 0; i < 50; ++i)
      for (int j = 0; j < 50; ++j)
        cache[i][j] = EMPTY;

    std::cin >> n;
    for (int i = 0; i < n; ++i) {
      int num;
      std::cin >> num;

      board[i] = num;
    }

    std::cout << play(0, n - 1) << std::endl;
    --n_case;
  }
  return 0;
}
