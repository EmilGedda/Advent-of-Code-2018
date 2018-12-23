#include <vector>
#include <algorithm>
#include <iostream>
#include <cstdio>
#include <cassert>
#include <cmath>

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

  while(y_diff(points) > 9)
    std::for_each(points.begin(), points.end(), step_forward);

  auto [top_left, bottom_right] 
    = std::minmax_element(points.begin(), points.end(), 
        [](const auto& a, const auto& b) {
          return std::hypot(a.x, a.y) < std::hypot(b.x, b.y);
        });

  auto diffx  = top_left->x,
       diffy  = top_left->y,
       width  = bottom_right->x - diffx,
       height = bottom_right->y - diffy + 1;

  std::vector<bool> grid(width*height);
  for(const auto& p: points)
    grid[(p.y - diffy)*width + p.x - diffx] = true;

  for(auto y = 0; y < height; y++) {
    for(auto x = 0; x < width; x++) {
      std::cout << (grid[y * width + x] ? '#' : ' ');
    }
    std::cout << '\n';
  }

  return 0;
}
