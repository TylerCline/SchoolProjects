#include <vector>
#include <string>
using namespace std;

struct player {
  string name;
  int points;
};

class PlayerHeap {

public:

  void add_player(string name, int points);
  void remove_player(string name);

  void update_player(string name, int points);

  void order_players();
  void top_player();

  void max_heap2(int size);
  void shift(int i, int child);

private:
  vector<player> player_heap;
};
