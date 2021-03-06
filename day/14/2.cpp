#include <vector>
#include <array>
#include <algorithm>

constexpr std::array ending = { 7, 9, 3, 0, 6, 1 };

auto solve() {
  std::vector recipes = {3, 7};
  auto elf_a = 0, elf_b = 1;

  while(!std::includes(recipes.end() - ending.size() - 1, recipes.end(), ending.begin(), ending.end())) {
    auto sum = recipes[elf_a] + recipes[elf_b];
    if(sum >= 10)
      recipes.push_back(1);
    recipes.push_back(sum % 10);
    elf_a = (elf_a + recipes[elf_a] + 1) % recipes.size();
    elf_b = (elf_b + recipes[elf_b] + 1) % recipes.size();
  }

  return recipes.size() - ending.size() - 1;
}
