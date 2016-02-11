#include <iostream>
#include "CircleTheWordSolver.h"
#include <vector>
#include <string>
using namespace std;

int main() {
  int n, m;
  cin >> n;
  cin >> m;
  vector<vector<char> > puzzle;
  puzzle.resize(n);
  for (size_t i=0;i<n;i++) {
    puzzle[i].resize(m);
    for (size_t j=0;j<m;j++) {
      char c;
      cin >> c; // ignore whitespace
      if (!cin.fail()) {
	puzzle[i][j] = c;
      } else {
	cout << "Bad input --- puzzle" << endl;
	exit(-1);
      }
    }
  }
  int k;
  cin >> k; // # of words;

  vector<string> wordlist;
  for (size_t i=0;i<k; i++) {
    string t;
    cin >> t;
    if (!cin.fail()) {
      wordlist.push_back(t);
    } else {
      cout << "Bad Input --- wordlist"  << endl;
    }
  }
  vector<pair<int, int> > locations;
  CircleTheWordSolver obj;

  locations = obj.word_locations(puzzle,wordlist);
  
  for (size_t i=0;i<locations.size();i++) {
    if (locations[i] == make_pair(-1,-1) ) {
      cout << wordlist[i] << " not found " << endl;
    } else {
      cout << wordlist[i] << " found at location " << locations[i].first << "," << locations[i].second << endl;
    }
  }
}
