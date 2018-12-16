#include <algorithm>
#include <cstdio>
#include <array>
#include <tuple>
#include <vector>

auto solve() {
  int id, x, y, w, h;
  std::array<int, 1000*1000> fabric = { 0 };
  std::vector<std::tuple<int, int, int, int>> claim;
  while(std::scanf("#%d @ %d,%d: %dx%d\n", &id, &x, &y, &w, &h) == 5) {
    claim.emplace_back(x, y, w, h);
    for(auto i = x; i < x + w; i++) {
      for(auto j = y; j < y + h; j++) {
        fabric[i * 1000 + j]++;
      }
    }
  }
  return std::count_if(fabric.begin(), fabric.end(),
	  [](int x) { return x > 1; });
}
