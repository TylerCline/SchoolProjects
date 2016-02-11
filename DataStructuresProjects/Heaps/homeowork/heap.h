#include <vector>
#include <string>
using namespace std;

struct player {
  int points;
};

class PlayerHeap {

public:

  void add_player(int points);

  void max_heap2(int size);
  void max_heapify(int a, int compare_num);
  void shift(int i, int child, int compare_num);

private:
  vector<player> player_heap;
};
