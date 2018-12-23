#include <iostream>
#include <chrono>

extern long long solve();

int main() {
  std::ios::sync_with_stdio(false);
  using namespace std::chrono;
  auto start  = steady_clock::now();
  auto answer = solve();
  auto end    = steady_clock::now();

  const auto solution = SOLUTION;
  std::cout << "Day " << solution[0] << ", problem " << solution[2] << "\n"
    << "Answer: " << answer << "\nExecution time: " 
    << duration_cast<duration<float>>(end - start).count() << "s\n";

}
