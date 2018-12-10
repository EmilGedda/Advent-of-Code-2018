#include <algorithm>
#include <charconv>
#include <string>
#include <vector>
#include <iostream>

std::string react(const std::string& polymer) {
	std::vector<char> stack;
	for (auto i = 0u; i < polymer.size(); i++) {
		if (stack.empty()) {
			stack.push_back(polymer[i]);
		}
		else {
			if (std::toupper(polymer[i]) == std::toupper(stack[stack.size() - 1])
				&& polymer[i] != stack[stack.size() - 1])
				stack.pop_back();
			else
				stack.push_back(polymer[i]);
		}
	}
	return { stack.begin(), stack.end() };
}

auto solve() {
	std::string polymer;
	std::cin >> polymer;
	auto shortest = polymer.size();
	for (auto i = 'a'; i <= 'z'; i++) {
		auto shorter_polymer = polymer;
			shorter_polymer.erase(std::remove_if(shorter_polymer.begin(), shorter_polymer.end(),
				[&](const auto& c) { return i == c || std::toupper(i) == c;}), shorter_polymer.end());
		shortest = std::min(shortest, react(shorter_polymer).size());
	}
	return shortest;
}