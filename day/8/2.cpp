#include <iostream>
#include <vector>
#include <numeric>

struct node {
  std::vector<node> children;
  std::vector<unsigned int> metadata;
};

node parse(std::istream& stream) {
  node n;
  int num_children, num_metadata, tmp;
  stream >> num_children >> num_metadata;

  for(int i = 0; i < num_children; i++)
    n.children.push_back(parse(stream));

  for(int i = 0; i < num_metadata; i++) {
    stream >> tmp;
    n.metadata.push_back(tmp);
  }

  return n;
}

auto value(const node& n) {
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
  return value(parse(std::cin));
}
