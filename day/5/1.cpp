#include <iostream>
#include <string>

std::string recurse(const std::string& polymer) {
  for(auto i = 0u; i < polymer.size() - 1; i++) {
    if((polymer[i] & 32) != (polymer[i+1] & 32)
       && (polymer[i] | 32) == (polymer[i+1] | 32))
      return recurse(polymer.substr(0, i) + polymer.substr(i + 2));
  }
  return polymer;
}

auto solve() {
  std::string input;
  std::cin >> input;
  return recurse(input).size();
}
