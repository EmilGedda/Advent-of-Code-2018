#include <algorithm>
#include <optional>
#include <utility>
#include <set>
#include <string>
#include <iostream>
#include <unordered_map>
#include <vector>

struct position {
  int x;
  int y;

  void operator+=(const position& rhs) {
    x += rhs.x;
    y += rhs.y;
  }

  bool operator<(const position& rhs) const {
    return y != rhs.y ? y < rhs.y : x < rhs.x;
  }

  bool operator==(const position& rhs) const {
    return y == rhs.y && x == rhs.x;
  }
};

namespace std {
  template <>
    struct hash<position> {
      std::size_t operator()(const position& p) const {
        std::hash<int> hasher;
        auto x = hasher(p.x);
        return x ^ (hasher(p.y) + 0x9e3779b9 + (x << 6) + (x >> 2));
      }
    };
}

constexpr std::array directions = { '^', '>', 'v', '<' };
std::unordered_map<char, position> velocities = {
  { '^', { 0, -1 } },
  { '>', { 1,  0 } },
  { 'v', { 0,  1 } },
  { '<', { -1, 0 } }
};

struct cart {
  int intersection = -1;
  int direction;
  position pos;
  bool alive = true;

  cart(int d, position p) : direction(d), pos(p) { }

  char turn(char track) {
    const auto it = std::find(directions.begin(), directions.end(), direction);
    auto new_direction = std::distance(directions.begin(), it);

    auto left = (track == '\\' && (direction == '^' || direction == 'v'))
             || (track == '/'  && (direction == '>' || direction == '<'));

    if(track == '+') {
      intersection = (intersection + 1) % 3;
      if(intersection == 0)
        left = true;
      if(intersection == 1)
        return direction;
    }

    new_direction += left ? -1: 1;
    return directions[new_direction % directions.size()];
  }

  bool operator<(const cart& rhs) const {
    return pos < rhs.pos;
  }

  bool operator==(const cart& rhs) const {
    return pos == rhs.pos;
  }

  void move(char track) {
    if(track != '|' && track != '-')
      direction = turn(track);
    pos += velocities[direction];
  }
};

struct minecart_network {
  std::unordered_map<position, char> map;
  std::vector<cart> carts; 

  minecart_network(std::istream& stream) {
    int x = -1, y = 0;
    char track;
    while(!stream.get(track).eof()) {
      x++;
      position pos = {x, y};
      auto direction = std::find(directions.begin(), directions.end(), track);
      if(direction != directions.end()) {
        carts.emplace_back(*direction, pos);
        if(*direction == '^' || *direction == 'v')
          map[pos] = '|';
        else
          map[pos] = '-';
      } else if(track == '\n') {
        y++;
        x = -1;
      } else {
        map[pos] = track;
      }
    }
  }

  std::optional<position> tick() {
    for(auto i = 0u; i < carts.size(); i++) {
      auto& c = carts[i];
      if(!c.alive) continue;
      c.move(map[c.pos]);
      if(std::count(carts.begin(), carts.end(), c) > 1) {
        for(auto& collision: carts)
          if(collision == c)
            collision.alive = false;
      }
    }

    carts.erase(std::remove_if(carts.begin(), carts.end(), 
          [](const auto& c) { return !c.alive; }), carts.end());

    if(carts.size() == 1) {
      auto& c = carts[0];
      return c.pos;
    }

    std::sort(carts.begin(), carts.end());
    return std::nullopt;
  }

};

auto solve() {
  minecart_network network(std::cin);
  std::optional<position> collision;

  while(!collision)
    collision = network.tick();

  std::cout << collision->x << ',' << collision->y;
  return 0;
}
