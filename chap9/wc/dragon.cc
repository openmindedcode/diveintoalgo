#include <string>
#include <iostream>

#include <cassert>

const int MAX = 1000 * 1000 * 1000 + 1;
int length[51];
const char *EXPAND_X = "X+YF";
const char *EXPAND_Y = "FX-Y";

void precalc() {
  length[0] = 1;
  for (int i = 1; i <= 50; ++i) {
    length[i] = std::min(MAX, length[i-1] * 2 + 2);
  }
}

char expand(const std::string& dragonCurve, int generations, int skip) {
  if (generations == 0) {
    assert(skip < dragonCurve.size());
    return dragonCurve[skip];
  }

  for (int i = 0; i < dragonCurve.size(); ++i) {
    if (dragonCurve[i] == 'X' || dragonCurve[i] == 'Y') {
      if (skip >= length[generations])
        skip -= length[generations];
      else if (dragonCurve[i] == 'X')
        return expand(EXPAND_X, generations - 1, skip);
      else
        return expand(EXPAND_Y, generations - 1, skip);
    } else if (skip > 0) {
      --skip;
    } else {
      return dragonCurve[i];
    }
  }
  return '#';
}

void dragon(int n, int p, int l) {
  for (int i = p - 1; i < p - 1 + l; ++i) {
    std::cout << expand("FX", n, i);
  }
  std::cout << std::endl;
}

int main() {
  int n_case;
  int n, p, l;

  precalc();

  std::cin >> n_case;
  while (n_case > 0) {
    std::cin >> n >> p >> l;
    dragon(n, p, l);
    --n_case;
  }

  return 0;
}
