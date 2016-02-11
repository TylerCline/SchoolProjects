#include <iostream>
#include <cstdlib>
#include "heap.h"
using namespace std;

int main() {
  char option;
  int points = 0;

  PlayerHeap my_league;
  for(int i = 0; i < 5; i++)
       {points = rand()%100 + 1; //Generate numbers between 100 - 1
        my_league.add_player(points);
        cout<<points<<" is added "<<endl;
       }

  for(int j = 0; j < 10; j++)
  {   points = rand()%100 + 1; //Generate numbers between 100 - 1
      my_league.add_player(points);
      cout<<points<<" is added "<<endl;
  }

  for(int i = 0; i < 15; i++)
  {   points = rand()%100 + 1; //Generate numbers between 100 - 1
      my_league.add_player(points);
      cout<<points<<" is added "<<endl;
  }

}
