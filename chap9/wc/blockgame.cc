#include <iostream>
#include <vector>
#include <cstring>

std::vector<int> moves;
char cache[1<<25];

inline int cell(int y, int x) {
  return 1 << (y * 5 + x);
}

void preCalc() {
  for (int y = 0; y < 4; ++y) {
    for (int x = 0; x < 4; ++x) {
      std::vector<int> cells;
      for (int dy = 0; dy < 2; ++dy) {
        for (int dx = 0; dx < 2; ++dx) {
          cells.push_back(cell(y + dy, x + dx));
        }
      }
      int square = cells[0] + cells[1] + cells[2] + cells[3];
      for (int i = 0; i < 4; ++i) {
        moves.push_back(square - cells[i]);
      }
    }
  }
  for (int i = 0; i < 5; ++i) {
    for (int j = 0; j < 4; ++j) {
      moves.push_back(cell(i, j) + cell(i, j+1));
      moves.push_back(cell(j, i) + cell(j+1, i));
    }
  }
}

char play(int board) {
  char& ret = cache[board];
  if (ret != -1)
    return ret;

  ret = 0;
  for (int i = 0; i < moves.size(); ++i) {
    if((moves[i] & board) == 0) {
      if (!play((board | moves[i]) == 0)) {
        ret = 1;
        break;
      }
    }
  }
  return ret;
}

int main() {
  int n_case;
  preCalc();

  std::cin >> n_case;

  while (n_case) {
    int board = 0;
    std::string line;
    std::memset(cache, -1, sizeof cache);

    for (int i = 0; i < 5; ++i) {
      std::cin >> line;
      for (int j = 0; j < line.size(); ++j) {
        if (line[j] == '#')
          board |= cell(i, j);
      }
    }

    std::cout << ((play(board) == 1) ? "LOSING" : "WINNING") << std::endl;

    --n_case;
  }
  return 0;
}
