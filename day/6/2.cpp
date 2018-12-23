#include <algorithm>
#include <cstdio>
#include <iostream>
#include <limits>
#include <numeric>
#include <set>
#include <vector>

struct owner {
  int id = -1;
  int best_distance = std::numeric_limits<int>::max();
};

struct point {
  int x;
  int y;
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

  auto max_x = it_max_x->x + 1,
       min_x = it_min_x->x - 1,
       max_y = it_max_y->y + 1,
       min_y = it_min_y->y - 1;

  std::vector<std::vector<owner>> grid(max_x + 1, 
                                      {static_cast<uint64_t>(max_y + 1), owner{}});

  for(auto i = min_x; i <= max_x; i++) {
    for(auto j = min_y; j <= max_y; j++) {
      for(auto id = 0u; id < coordinates.size(); id++) {
        auto [x, y] = coordinates[id];
        auto distance = std::abs(x - i) + std::abs(y - j);
        auto& cell = grid[i][j];
        if (distance == cell.best_distance)
          cell.id = -1;
        if(distance < cell.best_distance) {
          cell.id = id;
          cell.best_distance = distance;
        }
          
      }
    }
  }

  // mark all id's which border the grid as having infinite area
  std::set<int> infinite_area;

  // top row
  for(auto i = min_x; i <= max_x; i++)
    infinite_area.insert(grid[i][min_y].id);

  // bottom row
  for(auto i = min_x; i <= max_x; i++)
    infinite_area.insert(grid[i][max_y].id);

  // first column
  for(auto i = min_y; i <= max_y; i++)
    infinite_area.insert(grid[min_x][i].id);

  // last column
  for(auto i = min_y; i <= max_y; i++)
    infinite_area.insert(grid[max_x][i].id);

  std::vector<int> all_coordinates(coordinates.size());
  // fill with 0, 1, 2, ..., coordinates.size() - 1
  std::iota(all_coordinates.begin(), all_coordinates.end(), 0);

  std::vector<int> candidates;
  std::set_difference(all_coordinates.begin(), all_coordinates.end()
                    , infinite_area.begin(), infinite_area.end()
                    , std::back_inserter(candidates));

  std::vector<int> areas(coordinates.size(), 0);
  for(auto i = min_x; i <= max_x; i++) {
    for(auto j = min_y; j <= max_y; j++) {
      auto id = grid[i][j].id;
      if(id != -1)
        areas[id]++;
    }
  }

  auto best_candidate = *std::max_element(candidates.begin(), candidates.end(),
                          [&](const auto& a, const auto& b) { return areas[a] < areas[b]; });

  return areas[best_candidate];
}
