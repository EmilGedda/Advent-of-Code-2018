#include <vector>
#include <iterator>
#include <iostream>
#include <tuple>

struct node {
  std::vector<node> children;
  std::vector<int> metadata;
};

std::tuple<node, int, int> parse(const std::vector<int>& input, int idx) {
  node n;
  auto num_children = input[idx++];
  auto num_metadata = input[idx++];
  int sum_metadata = 0;
  for(int i = 0; i < num_children; i++) {
    const auto [child, new_idx, sum] = parse(input, idx);
    sum_metadata += sum;
    n.children.push_back(child);
    idx = new_idx;
  }

  for(int i = 0; i < num_metadata; i++) {
    sum_metadata += input[idx];
    n.metadata.push_back(input[idx++]);
  }

  return {n, idx, sum_metadata};
}

auto solve() {
  std::vector<int> input(std::istream_iterator<int>(std::cin), {});
  const auto [root, idx, sum_metadata] = parse(input, 0);
  return sum_metadata;
}
