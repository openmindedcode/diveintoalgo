#include <cstring>
#include <string>
#include <iostream>
#include <algorithm>

const int MOD = 1000 * 1000 * 1000 + 7;
std::string e, digits;
int n, m;
int cache[1<<14][20][2];

int price(int index, int taken, int mod, int less) {
  if (index == n)
    return (less && mod == 0) ? 1 : 0;

  int& ret = cache[taken][mod][less];
  if (ret != -1)
    return ret;
  ret = 0;

  for (int next = 0; next < n; ++next) {
    if ((taken & (1<<next)) == 0) {
      if (!less && e[index] < digits[next])
        continue;

      if (next > 0 && digits[next-1] == digits[next] &&
          (taken & (1<<(next-1))) == 0)
        continue;
      int nextTaken = taken | (1<<next);
      int nextMod = (mod * 10 + digits[next] - '0') % m;
      int nextLess = less || e[index] > digits[next];
      ret += price(index+1, nextTaken, nextMod, nextLess);
      ret %= MOD;
    }
  }
  return ret;
}

int main() {
  int n_case;
  std::cin >> n_case;

  while (n_case > 0) {
    std::cin >> e >> m;

    n = e.length();
    digits = e;
    sort(digits.begin(), digits.end());

    std::memset(cache, -1, sizeof cache);
    std::cout << price(0, 0, 0, 0) << std::endl;

    --n_case;
  }
  return 0;
}
