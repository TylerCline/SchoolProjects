//
// File: MWVC.cc
// Purpose: This code finds the minimum weighted vertex cover in a graph by 
// using brute force search.
// Author: David W. Juedes
// 
#include <iostream>
#include <vector>
#include <set>
#include <list>
#include <sstream>
#include <thread>

using namespace std;

//Number of threads for the program
static const int num_threads = 10;
//
// isVertexCover: 
//
bool isVertexCover(vector<list<int> > &adj_list,
                    set<int> &min_set) {

  //for (set<int>::iterator p=max_set.begin();p!=max_set.end();++p) {
  for (size_t i=0;i<adj_list.size();i++) {
    if (min_set.count(i) > 0) continue; // All edges are covered.
    for (list<int>::iterator p1=adj_list[i].begin();
         p1!=adj_list[i].end();++p1) {
      if (min_set.count(*p1) == 0) return false; // Not a vertex cover
    }
  }
  return true;
}

void min_weighted_vc(vector<list<int> > &adj_list,
                     vector<double> & weights,
                     set<int> &min_set,    // Current max IS
                     double &prev_min )     // Current max weight) 
{
  size_t n = adj_list.size();
  for (size_t i = 1;i<(1<< n);i++) { // Works up to 31?
    set<int> t;
    for (size_t j = 0;j<32;j++) {
      if ((i& (1<<j)) > 0) t.insert(j);
    }
    if (isVertexCover(adj_list,t)) {
      double w=0;
      for (set<int>::iterator p=t.begin();p!=t.end();++p) {
        w+=weights[*p];
      }
      if (w<prev_min) { prev_min = w; min_set = t;}
    }
  }
}

int main() {
  int n;
  cin >> n;
  vector<double> weights;
  double sum = 0;
  for (int i=0;i<n;i++) {
    double w;
    cin >> w;
    weights.push_back(w);
    sum+=w;
  }

  vector<list<int> > adj_list;
  adj_list.resize(n);
  while (!cin.eof()) {
    string line;
    getline(cin,line);
    if (!cin.fail()) {
      istringstream in(line);
      int j;
      in >> j;  // Vertex #
      while (!in.eof()) {
        int k;
        in >> k;
        if (!in.fail()) {
          adj_list[j].push_back(k);
        }
      }
    }
  }

  double prev_min = sum;
  set<int> min_set;
  //Declare an array of threads 
  thread t[num_threads];
  //Iterate through the array of threads and initialize each spot to the function
  for(int i = 0; i < num_threads; ++i){
      t[i] = std::thread(min_weighted_vc, ref(adj_list), ref(weights), ref(min_set), ref(prev_min));
  }

  //Wait for each thread to finish
  for(int i = 0; i < num_threads; ++i){
      t[i].join();
  }

  cout << "Weight of minimum VC = " << prev_min << endl;
  cout << "Best Set = " << endl;
  for (set<int>::iterator p = min_set.begin();
       p!=min_set.end();++p) {
    cout <<*p << " weight = " << weights[*p] << endl;
  }
  cout << endl;
}

