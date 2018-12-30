#include "computer.hpp"
#include <string>
#include <iterator>
#include <algorithm>
#include <set>

auto solve() {
  opcode op;
  word a, b, output;
  std::set<std::string> all_opcodes;
  for(const auto& [name, _] : instruction_set) 
    all_opcodes.insert(name);

  std::array<std::set<std::string>, 16> opcode_candidates;
  for (auto& candidate: opcode_candidates)
    candidate = all_opcodes;
    
  for (auto i = 0; i <= 750; i++) {
    registers before, after;

    std::scanf("Before: [%d, %d, %d, %d]\n", 
               &before[0], &before[1], &before[2], &before[3]);

    std::scanf("%d %d %d %d\n", &op, &a, &b, &output);

    std::scanf("After:  [%d, %d, %d, %d]\n", 
               &after[0], &after[1], &after[2], &after[3]);

    std::set<std::string> matching_opcodes;
    auto& candidate = opcode_candidates[op];
    for(const auto& [name, instr] : instruction_set) {
      if(instr(before, a, b, output) == after)
        matching_opcodes.insert(name);
    }

    // intersect previous candidates for this opcode with the new matching ops
    std::set<std::string> intersection;
    std::set_intersection(candidate.begin(), candidate.end(), 
                          matching_opcodes.begin(), matching_opcodes.end(),
                          std::inserter(intersection, intersection.begin()));
    candidate = std::move(intersection);
  }

  // remove candidate op_codes by a naive method of exclusion
  while(std::any_of(opcode_candidates.begin(), opcode_candidates.end(),
        [](const auto& candidate) { return candidate.size() > 1; })) {
    for(const auto& candidates: opcode_candidates) {
      if (candidates.size() > 1) continue;
      const auto& perfect_match = *candidates.begin();
      for(auto& others: opcode_candidates) {
        if (others.size() == 1) continue;
        others.erase(perfect_match);
      }
    }
  }

  // run test program
  registers reg{};
  while(std::scanf("%d %d %d %d", &op, &a, &b, &output) != -1)
    reg = instruction_set.at(*opcode_candidates[op].begin())(reg, a, b, output);

  return reg[0];
}