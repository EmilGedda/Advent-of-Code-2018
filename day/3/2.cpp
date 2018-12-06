#include <iostream>
#include <cstdio>
#include <array>
#include <tuple>
#include <vector>

int main() {
  int id, x, y, w, h;
  char tmp;
  std::array<int, 1000*1000> fabric = { 0 };
  std::vector<std::tuple<int, int, int, int, int>> claims;
  while(std::scanf("#%d @ %d,%d: %dx%d\n", &id, &x, &y, &w, &h) == 5) {
    claims.emplace_back(id, x, y, w, h);
    for(int i = x; i < x + w; i++) {
      for(int j = y; j < y + h; j++) {
        fabric[i * 1000 + j]++;
      }
    }
  }
  for(const auto [id, x, y, w, h]: claims) {
    int sum = 0;
    for(int i = x; i < x + w; i++) {
      for(int j = y; j < y + h; j++) {
        sum += fabric[i * 1000 + j];
      }
    }
    if(sum == w * h) {
      std::cout << id << '\n';
      return 0;
    }
  }
}
