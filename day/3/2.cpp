#include <iostream>
#include <cstdio>
#include <array>
#include <tuple>
#include <vector>

auto solve() {
  int id, x, y, w, h;
  std::array<int, 1000*1000> fabric = { 0 };
  std::vector<std::tuple<int, int, int, int, int>> claims;
  while(std::scanf("#%d @ %d,%d: %dx%d\n", &id, &x, &y, &w, &h) == 5) {
    claims.emplace_back(id, x, y, w, h);
    for(auto i = x; i < x + w; i++) {
      for(auto j = y; j < y + h; j++) {
        fabric[i * 1000 + j]++;
      }
    }
  }
  for(const auto& [id, x, y, w, h]: claims) {
    auto sum = 0;
    for(auto i = x; i < x + w; i++) {
      for(auto j = y; j < y + h; j++) {
        sum += fabric[i * 1000 + j];
      }
    }
    if(sum == w * h) {
      return id;
    }
  }
  return -1;
}
