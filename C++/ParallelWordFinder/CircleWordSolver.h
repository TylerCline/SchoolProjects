#include <vector>
#include <string>
#include <algorithm>
using namespace std;

#ifndef DWJ_WORD_CIRCLE_DEF
#define DWJ_WORD_CIRCLE_DEF
class CircleTheWordSolver {
 public:
  vector<pair<int, int> > word_locations(
         vector<vector<char> > &puzzle, 
         vector<string> &wordlist);
};
#endif
