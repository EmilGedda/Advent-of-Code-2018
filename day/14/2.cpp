#include <vector>
#include <array>
#include <algorithm>
#include <iostream>

constexpr std::array ending = { 7, 9, 3, 0, 6, 1 };

auto solve() {
  std::vector<int> recipes = {3, 7};
  auto elf_a = 0, elf_b = 1;

  while(!std::includes(recipes.end() - ending.size() - 1, recipes.end()
                     , ending.begin(), ending.end())) {
    auto sum = recipes[elf_a] + recipes[elf_b];
    if(sum >= 10)
      recipes.push_back((sum / 10) % 10);
    recipes.push_back(sum % 10);
    elf_a = (elf_a + recipes[elf_a] + 1) % recipes.size();
    elf_b = (elf_b + recipes[elf_b] + 1) % recipes.size();
  }

  std::cout << recipes.size() - ending.size() - 1 << '\n';

  return 0;
}
