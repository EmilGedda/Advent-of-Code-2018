#include <algorithm>
#include <array>
#include <charconv>
#include <iostream>
#include <limits>
#include <numeric>
#include <string>
#include <unordered_map>
#include <vector>

auto solve() {
  std::string line;
  std::vector<std::string> lines;
  while(std::getline(std::cin, line)) {
    lines.emplace_back(std::move(line));
  }
  std::sort(lines.begin(), lines.end());

  std::unordered_map<int, std::array<int, 60>> sleep_time;
  for(auto i = 0u; i < lines.size();) {
    int guard, falls_asleep, wakes_up;
    std::sscanf(lines[i++].c_str()+26, "%d", &guard);
    while(i < lines.size() && lines[i][30] == 'p') {
      std::sscanf(lines[i++].c_str()+15, "%d", &falls_asleep);
      std::sscanf(lines[i++].c_str()+15, "%d", &wakes_up);
      for(auto j = falls_asleep; j < wakes_up; j++)
        sleep_time[guard][j]++;
    }
  }

  int sleepiest_guard = 0;
  int best_minute = 0;
  int longest_sleep = std::numeric_limits<int>::min();

  for(const auto& [guard, schedule]: sleep_time) {
    auto total_sleep = std::accumulate(schedule.begin(), schedule.end(), 0);
    auto minute = std::max_element(schedule.begin(), schedule.end());
    if(total_sleep > longest_sleep) {
      sleepiest_guard = guard;
      best_minute = std::distance(schedule.begin(), minute);
      longest_sleep = total_sleep;
    }
  }

  return sleepiest_guard * best_minute;
}
