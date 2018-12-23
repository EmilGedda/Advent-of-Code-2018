#include <unordered_map>
#include <set>
#include <queue>
#include <optional>
#include <utility>
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

  std::array<std::optional<std::pair<char, int>>, 5> timetable{};
  std::queue<char> q;
  int seconds = 0;

  for(const auto& root: roots)
    q.push(root);

  int processed = 0;
  while(processed < 26) {
    for(auto& worker: timetable) {
      if(!worker) continue;
      const auto [step, start_time] = *worker;
      if(seconds <= (step - 'A' + start_time + 60)) continue;
      for(auto n: dependents[step]) {
        dependencies[n].erase(step);
        if(dependencies[n].empty())
          q.push(n);
      }
      processed++;
      worker = std::nullopt;
    }
    // distribute new work
    for(auto& worker: timetable) {
      if(worker || q.empty()) continue;
      worker = {q.front(), seconds};
      q.pop();
    }
    seconds++;
  }

  return seconds - 1;
}
