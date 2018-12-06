#include <iostream>
#include <cstdio>
#include <array>
#include <tuple>
#include <vector>

int main() {
  int id, x, y, w, h;
  char tmp;
  std::array<int, 1000*1000> fabric = { 0 };
  std::vector<std::tuple<int, int, int, int>> claim;
  while(std::scanf("#%d @ %d,%d: %dx%d\n", &id, &x, &y, &w, &h) == 5) {
    claim.emplace_back(x, y, w, h);
    for(int i = x; i < x + w; i++) {
      for(int j = y; j < y + h; j++) {
        fabric[i * 1000 + j]++;
      }
    }
  }
  int count = 0;
  for(auto square: fabric) {
    count += square > 1;
  }
  std::cout << count << '\n';
}
