#include <vector>
#include <iostream>

constexpr auto n = 793061;

auto solve() {
  std::vector recipes = {3, 7};
  auto elf_a = 0, elf_b = 1;
  while(recipes.size() < n + 10) {
    auto sum = recipes[elf_a] + recipes[elf_b];
    if(sum >= 10)
      recipes.push_back(1);
    recipes.push_back(sum % 10);
    elf_a = (elf_a + recipes[elf_a] + 1) % recipes.size();
    elf_b = (elf_b + recipes[elf_b] + 1) % recipes.size();
  }

  for(auto i = n; i < n + 10; i++)
    std::cout << recipes[i];
  std::cout << '\n';

  return 0;
}
