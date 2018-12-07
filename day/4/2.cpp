
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

  std::array<std::pair<int, int>, 60> most_frequent;
  for(const auto& [guard, schedule]: sleep_time) {
    for(int minute = 0; minute < 60; minute++) {
      if(most_frequent[minute].second < schedule[minute]) {
        most_frequent[minute] = {guard, schedule[minute]};
      }
    }
  }

  auto minute = std::max_element(most_frequent.begin(), most_frequent.end(),
      [](const auto& a, const auto& b) { return a.second < b.second; });
  return minute->first * std::distance(most_frequent.begin(), minute);
}
