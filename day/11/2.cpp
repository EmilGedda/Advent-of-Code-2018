#include <array>
#include <iostream>

constexpr auto serial = 3214;

auto powerlevel(int x, int y) {
  auto rack_id = x + 10;
  auto power = (rack_id * y + serial) * rack_id;
  return ((power / 100) % 10) - 5;
}

auto solve() {
  std::array<int, 300*300> grid;
  for(auto y = 0; y < 300; y++) {
    for(auto x = 0; x < 300; x++)
      grid[y * 300 + x] = powerlevel(x, y);
  }

  // very naive - could be improved through Kadane's 2D algorithm
  int best_x, best_y, power_sum = 0, size;
  for(auto current_size = 1; current_size <= 299; current_size++) {
    for(auto y = 0; y < 300 - current_size; y++) {
      for(auto x = 0; x < 300 - current_size; x++) {
        auto power_square = 0;
        for(auto i = y; i < y + current_size; i++) {
          for(auto j = x; j < x + current_size; j++)
            power_square += grid[i * 300 + j];
        }
        if(power_square > power_sum) {
          best_x = x;
          best_y = y;
          power_sum = power_square;
          size = current_size;
        }
      }
    }
  }
  std::cout << best_x << ',' << best_y << ',' << size << '\n'; 
  return power_sum;
}
