#include "computer.hpp"
#include <string>

auto solve() {
  registers before, after;
  opcode op;
  word a, b, output;
  auto sum = 0;
  for (auto i = 0; i <= 750; i++) {
    std::scanf("Before: [%d, %d, %d, %d]\n", 
               &before[0], &before[1], &before[2], &before[3]);

    std::scanf("%d %d %d %d\n", &op, &a, &b, &output);

    std::scanf("After:  [%d, %d, %d, %d]\n", 
               &after[0], &after[1], &after[2], &after[3]);

    auto matching_opcodes = 0;
    for(const auto& [_, instr] : instruction_set) {
      matching_opcodes += instr(before, a, b, output) == after;
    }
    sum += matching_opcodes >= 3;
  }
  return sum;
}
