#include "heap.h"
#include <iostream>

void PlayerHeap::add_player(int points)
{
  player p;
  p.points = points;

  for(int i = 0; i < player_heap.size(); i++)
   {
    if(player_heap[i].points == points)
     {
       cout << "already in heap" << endl;
       return;
     }
   }

  player_heap.push_back(p);
  max_heap2(player_heap.size());
}


void PlayerHeap::max_heap2(int size)
{ int comparisons = 0;
  for(int i = size; i > 0; i--)
  {
    max_heapify(i, comparisons);
    /*if(player_heap[parent].points < player_heap[i].points)
        {comparisons++;
         shift(parent, i);

         if(i/2 < 0)
            return;
        }
  }*/
}
}

void PlayerHeap::max_heapify(int a, int compare_num)
{ int parent = a/2;
  if(player_heap[parent].points > player_heap[a].points)
  {
     return;}
  else {
     compare_num++;
     shift(parent, a, compare_num);
     max_heapify(a, compare_num);
  }
  cout<<compare_num<<" when ";
}
void PlayerHeap::shift(int i, int child, int compare_num)
{
  player tmp = player_heap[i];
  player_heap[i] = player_heap[child];
  player_heap[child] = tmp;
}
