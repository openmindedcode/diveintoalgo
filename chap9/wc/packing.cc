#include <iostream>
#include <sstream>
#include <limits>
#include <cstring>
#include <vector>

using Item = struct {
  std::string name;
  int volume;
  int desire;
};

int cache[1001][100];

int pack(int capacity, int current_item, int n_item, int total_capacity,
    Item items[]) {
  if (current_item == n_item)
    return 0;

  int &ret = cache[capacity][current_item];
  if (ret != -1)
    return ret;

  ret = pack(capacity, current_item + 1, n_item, total_capacity, items);
  if (capacity >= items[current_item].volume)
    ret = std::max(ret, pack(capacity - items[current_item].volume,
          current_item + 1, n_item, total_capacity, items)
              + items[current_item].desire);
  return ret;
}

void reconstruct(int capacity, int current_item, std::vector<Item>& picked,
    int n_item, int total_capacity, Item items[]) {
  if (current_item == n_item)
    return;

  if (pack(capacity, current_item, n_item, total_capacity, items)
      == pack(capacity, current_item+1, n_item, total_capacity, items)) {
    reconstruct(capacity, current_item+1, picked, n_item, total_capacity, items);
  } else {
    picked.push_back(items[current_item]);
    reconstruct(capacity - items[current_item].volume, current_item + 1,
        picked, n_item, total_capacity, items);
  }
}


int main() {
  int n_case = 0;
  std::cin >> n_case;

  for (int i = 0; i < n_case; ++i) {
    int n_item, total_capacity;
    std::cin >> n_item >> total_capacity;

    // skip the next newline
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    // reset cache
    std::memset(cache, -1, sizeof(cache));

    Item items[n_item];

    for (int j = 0; j < n_item; ++j) {
      std::string line;
      std::getline(std::cin, line);

      std::string token;
      std::istringstream lineStream(line);
      std::getline(lineStream, token, ' ');
      items[j].name = token;
      std::getline(lineStream, token, ' ');
      items[j].volume = std::atoi(token.c_str());
      std::getline(lineStream, token, ' ');
      items[j].desire = std::atoi(token.c_str());
    }

    std::vector<Item> picked;
    reconstruct(0, 0, picked, n_item, total_capacity, items);

    // print result
    int result_desire = 0;
    for (const auto & i : picked) {
      result_desire += i.desire;
    }
    std::cout << picked.size() << " " << result_desire << std::endl;
    for (const auto& i : picked) {
      std::cout << i.name << std::endl;
    }

  }
  return 0;
}
