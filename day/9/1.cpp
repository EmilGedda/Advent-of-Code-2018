#include <cstdio>
#include <vector>
#include <list>
#include <algorithm>

template<typename T>
void wrapped_decrement(std::list<int>& marbles, T& iterator, int n) {
  for(int i = 0; i < n; i++) {
    if(iterator == marbles.begin())
      iterator = marbles.end();
    iterator--;
  }
}

template<typename T>
void wrapped_increment(std::list<int>& marbles, T& iterator, int n) {
  for(int i = 0; i < n; i++) {
    iterator++;
    if(iterator == marbles.end())
      iterator = marbles.begin();
  }
}

auto solve() {
  int players, final_marble = 0;
  std::list<int> marbles;
  std::scanf("%d players; last marble is worth %d points", &players, &final_marble);
  std::vector<int> scores(players);
  marbles.push_back(0);
  auto current_marble = marbles.begin();
  for(auto marble = 1; marble <= final_marble; marble++) {
    if(marble % 23 == 0) {
      auto current_player = (marble - 1) % players;
      wrapped_decrement(marbles, current_marble, 7);
      scores[current_player] += marble + *current_marble;
      current_marble = marbles.erase(current_marble);
    } else {
      wrapped_increment(marbles, current_marble, 2);
      current_marble = marbles.insert(current_marble, marble);
    }
  }
  return *std::max_element(scores.begin(), scores.end());
}
