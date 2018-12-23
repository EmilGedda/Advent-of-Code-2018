#include <vector>
#include <algorithm>
#include <cstdio>

struct point {
  int x;
  int y;
  int dx;
  int dy;
};

void step_forward(point& p) {
  p.x += p.dx;
  p.y += p.dy;
}

auto solve() {
  int x, y, dx, dy;
  std::vector<point> points;
  while(std::scanf("position=<%d, %d> velocity=<%d, %d>\n", &x, &y, &dx, &dy) == 4)
    points.push_back({x, y, dx, dy});

  const auto y_diff = [](const auto& p) {
    const auto [min_y, max_y] = std::minmax_element(p.begin(), p.end(),
        [](const auto& a, const auto& b) { return a.y < b.y; });
    return max_y->y - min_y->y;
  };

  int seconds = 0;
  while(y_diff(points) > 9) {
    std::for_each(points.begin(), points.end(), step_forward);
    seconds++;
  }

  return seconds;
}
