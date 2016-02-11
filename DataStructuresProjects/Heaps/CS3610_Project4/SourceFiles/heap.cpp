#include "heap.h"
#include <iostream>

void PlayerHeap::add_player(string name, int points)
{
  player p;
  p.name = name;
  p.points = points;

  for(int i = 0; i < player_heap.size(); i++)
   {
    if(player_heap[i].name == name)
     {
       cout << "Player already in heap" << endl;
       return;
     }
   }

  player_heap.push_back(p);
  max_heap2(player_heap.size());
}

void PlayerHeap::remove_player(string name) {

  for(int i = 0; i < player_heap.size(); i++)
  {
       if(player_heap[i].name == name )
      {
          player tmp = player_heap.back();
          player_heap.back() = player_heap[i];
          player_heap[i] = tmp;
          player_heap.pop_back();
          max_heap2(player_heap.size());
          return;
      }
  }
 cout<< "Player not found" << endl;
}

void PlayerHeap::update_player(string name, int points) {

  for(int i = 0; i < player_heap.size(); i++)
  {
      if(player_heap.empty())
      {
          cout<<"No players on record " << endl;
      }
      else if(player_heap[i].name == name)
      {
          player_heap[i].points += points;
            //build_heap();

            max_heap2(player_heap.size());
            return;
      }
  }
 cout << "Player not found " << endl;
}

void PlayerHeap::order_players() {

   vector<player> sorted_heap;
   int size = player_heap.size()-1;

   for(int i = player_heap.size()-1; i >= 0; i-- )
   {
       player tmp = player_heap[0];
       player_heap[0] = player_heap[i];
       player_heap[i] = tmp;
       sorted_heap.push_back(player_heap[i]);
       size--;
       max_heap2(size);
   }

   for(int i = 0; i < sorted_heap.size(); i++)

   {
     cout << sorted_heap[i].name << ": " << sorted_heap[i].points<<endl;
   }
   max_heap2(player_heap.size());
}

void PlayerHeap::top_player()
{   int points = 0;
    string name;
    for(int i = 0; i < player_heap.size(); i++)
    {
        if(player_heap[i].points > points)
        {
            points = player_heap[i].points;
            name = player_heap[i].name;
        }
    }
    cout<<name<<": "<<points<<endl;
}


void PlayerHeap::max_heap2(int size)
{
  for(int i = size; i > 0; i--)
  {
    int parent = i/2;
    if(player_heap[parent].points < player_heap[i].points)
        {
         shift(parent, i);

         if(i/2 < 0)
            return;
        }
  }
}
void PlayerHeap::shift(int i, int child)
{
  player tmp = player_heap[i];
  player_heap[i] = player_heap[child];
  player_heap[child] = tmp;
}
