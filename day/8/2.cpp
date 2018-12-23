#include <vector>
#include <iterator>
#include <iostream>
#include <utility>
#include <numeric>

struct node {
  std::vector<node> children;
  std::vector<unsigned int> metadata;
};

std::pair<node, int> parse(const std::vector<int>& input, int idx) {
  node n;
  auto num_children = input[idx++];
  auto num_metadata = input[idx++];
  for(int i = 0; i < num_children; i++) {
    const auto [child, new_idx] = parse(input, idx);
    n.children.push_back(child);
    idx = new_idx;
  }

  for(int i = 0; i < num_metadata; i++)
    n.metadata.push_back(input[idx++]);

  return {n, idx};
}

int value(const node& n) {
  if(n.children.empty())
    return std::accumulate(n.metadata.begin(), n.metadata.end(), 0);

  return std::accumulate(n.metadata.begin(), n.metadata.end(), 0,
      [&](auto sum, auto index) {
        if(index < 1 || index > n.children.size())
          return sum;
        return sum + value(n.children[index - 1]);
      });
}

auto solve() {
  std::vector<int> input(std::istream_iterator<int>(std::cin), {});
  const auto [root, _] = parse(input, 0);
  return value(root);
}
