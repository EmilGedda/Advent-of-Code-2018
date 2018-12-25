#include <unordered_map>
#include <vector>
#include <array>
#include <cstdio>
#include <iostream>
#include <string>

auto solve() {
  std::unordered_map<int, bool> plants;
  std::vector<std::array<bool, 5>> notes;

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
  for(auto generation = 0; generation < 20; generation++) {
    bool any_matched = false;
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
        any_matched = true;
        break;
      }
    }
    plants = std::move(next_generation);
    next_generation.clear();
    if(!any_matched) break;
  }

  int sum = 0;
  for(const auto& [pot, plant]: plants)
    sum += plant ? pot : 0;
  return sum;
}
