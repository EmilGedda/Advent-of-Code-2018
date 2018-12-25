#include <unordered_map>
#include <vector>
#include <array>
#include <cstdio>
#include <iostream>
#include <string>

auto solve() {
  std::unordered_map<int, bool> plants;
  std::vector<std::array<bool, 5>> notes;

  const auto pot_sum = [] (const auto& plants) {
    auto sum = 0;
    for(const auto& [pot, plant]: plants)
      sum += plant ? pot : 0;
    return sum;
  };

  std::string line;
  std::getline(std::cin, line);
  int left = -2;
  int right = line.size() - 12;
  for(auto i = 15u; i < line.size(); i++)
    plants[i - 15] = line[i] == '#';

  std::getline(std::cin, line); // empty line
  while(std::getline(std::cin, line)) {
    if(line[9] == '.') continue; // all "[...] => ." notes are useless
    notes.push_back({line[0] == '#', line[1] == '#', 
                     line[2] == '#', line[3] == '#',
                     line[4] == '#'});
  }
  std::unordered_map<int, bool> next_generation;
  auto sum = 0;
  constexpr auto max_generation = 100ull;
  for(auto generation = 0ull; generation < max_generation; generation++) {
    for(auto plant = left; plant <= right; plant++) {
      for(auto i = 0u; i < notes.size(); i++) {
        const auto& rule = notes[i];
        bool matches = true;
        for(auto j = 0; j < 5 && matches; j++)
          matches = rule[j] == plants[plant - 2 + j];
        if(!matches) continue;
        next_generation[plant] = true;
        left  = std::min(plant - 1, left);
        right = std::max(plant + 1, right);
        break;
      }
    }
    plants = std::move(next_generation);
    next_generation.clear();
    if(generation + 1 < max_generation)
      sum = pot_sum(plants);
  }

  uint64_t curr_sum = pot_sum(plants);
  const auto growth = curr_sum - sum;

  return curr_sum + growth * (50'000'000'000 - max_generation);
}
