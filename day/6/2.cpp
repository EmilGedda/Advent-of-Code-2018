#include <algorithm>
#include <cstdio>
#include <numeric>
#include <vector>

struct point {
  const int x;
  const int y;
};

auto solve() {
  int x, y;
  std::vector<point> coordinates;
  while(std::scanf("%d, %d\n", &x, &y) == 2)
    coordinates.push_back({x, y});

  auto [it_min_x, it_max_x] = std::minmax_element(coordinates.begin(), coordinates.end(),
                                [](const auto& a, const auto& b) { return a.x < b.x; });
                                          
  auto [it_min_y, it_max_y] = std::minmax_element(coordinates.begin(), coordinates.end(),
                                [](const auto& a, const auto& b) { return a.y < b.y; });

  const auto max_x = it_max_x->x + 1,
             min_x = it_min_x->x - 1,
             max_y = it_max_y->y + 1,
             min_y = it_min_y->y - 1;

  const auto cumulative_distance =
    [&](auto x, auto y) {
      return std::accumulate(coordinates.begin(), coordinates.end(), 0,
                [&](auto sum, const auto& p) {
                  return sum + std::abs(x - p.x) + std::abs(y - p.y);
                });
    };

  std::vector<bool> grid(max_x * max_y); 
  for(auto y = min_y; y < max_y; y++) { 
    for(auto x = min_x; x < max_x; x++) {
      grid[y * max_x + x] = cumulative_distance(x, y) < 10'000;
    }
  }

  return std::count(grid.begin(), grid.end(), true);
}
