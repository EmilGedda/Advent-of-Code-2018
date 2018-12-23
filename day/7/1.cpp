#include <unordered_map>
#include <set>
#include <string>
#include <iostream>
#include <cstdio>

auto solve() {

  std::unordered_map<char, std::set<char>> dependents;
  std::unordered_map<char, std::set<char>> dependencies;
  std::set<char> roots;

  for(auto c = 'A'; c <= 'Z'; c++)
    roots.insert(c);

  char a, b;
  auto format = "Step %c must be finished before step %c can begin.\n";

  while(std::scanf(format, &a, &b) == 2) {
    dependents[a].insert(b);
    dependencies[b].insert(a);
    roots.erase(b);
  }

  // Kahn's algorithm - topological sorting
  std::string plan_order;
  while(!roots.empty()) {
    auto step = roots.extract(roots.begin()).value();
    plan_order += step;
    for(auto m: dependents[step]) {
      dependencies[m].erase(step);
      if(dependencies[m].empty())
        roots.insert(m);
    }
  }

  std::cout << plan_order << '\n';
  return 0;
}
