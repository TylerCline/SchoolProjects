#include <iostream>
#include "heap.h"
using namespace std;

int main() {
  char option;
  string name, junk;
  int points;
  
  PlayerHeap my_league;

  do {
    cin >> option;
    switch(option) {
      case 'a':
        getline(cin, junk);
        getline(cin, name); 
        cin >> points;
        my_league.add_player(name, points);
        break;
      case 'r':
        getline(cin, junk);
        getline(cin, name);
        my_league.remove_player(name);
        break;
      case 'u':
        getline(cin, junk);
        getline(cin, name);
        cin >> points;
        my_league.update_player(name, points);
        break;
      case 'o':
        my_league.order_players();
        break;
      case 't':
        my_league.top_player();
        break; 
      default:
        break;
    } 
  } while(option != 'q');
}
