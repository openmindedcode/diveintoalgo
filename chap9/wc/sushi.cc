#include <iostream>
#include <cstring>

int n, m, price[20], pref[20];
int c[201];

int sushi() {
  int ret = 0;
  c[0] = 0;
  for (int budget = 1; budget <= m; ++budget) {
    int cand = 0;
    for (int dish = 0; dish < n; ++dish) {
      if (budget >= price[dish])
        cand = std::max(cand, c[(budget - price[dish]) % 201] + pref[dish]);
    }
    c[budget % 201] = cand;
    ret = std::max(ret, cand);
  }
  return ret;
}

int main() {
  int n_case;
  std::cin >> n_case;

  while (n_case) {
    std::cin >> n >> m;
    m /= 100;

    std::memset(c, 0, sizeof(c));

    for (int i = 0; i < n; ++i) {
      std::cin >> price[i] >> pref[i];
      price[i] /= 100;
    }

    std::cout << sushi() << std::endl;
    --n_case;
  }

  return 0;
}
