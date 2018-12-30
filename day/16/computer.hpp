#pragma once

#include <array>
#include <functional>
#include <string>
#include <unordered_map>

using word = int;
using registers = std::array<word, 4>;

enum opcode {
  add, 
  mul, 
  ban, 
  bor,
  set,
  gt,
  eq,
};

enum input_type {
  imm,
  reg
};

struct arguments
{
  const std::function<word(registers, word)>& first;
  const std::function<word(registers, word)>& second;

  arguments(input_type a, input_type b)
    : first(handlers[a]), second(handlers[b]) { }

private:
  inline const static std::array<std::function<word(registers, word)>, 2> handlers = {
    [](const registers, word immediate) { return immediate;},
    [](const registers regs, word index) { return regs[index];}
  };
};

struct instruction {
  const opcode op;
  const arguments args;
  
  static instruction create(opcode op, input_type first, input_type second) {
    return { op, {first, second} };
  }

  registers operator()(registers regs, word a, word b, size_t output) const {
    regs[output] = operations[op](args.first(regs, a), args.second(regs, b));
    return regs;
  }

private:
  inline const static std::array<std::function<word(word, word)>, 7> operations = {
    std::plus<>(),
    std::multiplies<>(),
    std::bit_and<>(),
    std::bit_or<>(),
    [](const word& a, word) { return a; }, // set
    std::greater<>(),
    std::equal_to<>()
  };
};

inline const std::unordered_map<std::string, instruction> instruction_set = {
  {"addr", instruction::create(add, reg, reg)},
  {"addi", instruction::create(add, reg, imm)},
  {"mulr", instruction::create(mul, reg, reg)},
  {"muli", instruction::create(mul, reg, imm)},
  {"banr", instruction::create(ban, reg, reg)},
  {"bani", instruction::create(ban, reg, imm)},
  {"borr", instruction::create(bor, reg, reg)},
  {"bori", instruction::create(bor, reg, imm)},
  {"setr", instruction::create(set, reg, imm)},
  {"seti", instruction::create(set, imm, imm)},
  {"gtir", instruction::create(gt, imm, reg)},
  {"gtri", instruction::create(gt, reg, imm)},
  {"gtrr", instruction::create(gt, reg, reg)},
  {"eqir", instruction::create(eq, imm, reg)},
  {"eqri", instruction::create(eq, reg, imm)},
  {"eqrr", instruction::create(eq, reg, reg)},
};