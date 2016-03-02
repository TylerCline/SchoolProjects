//
// File: Updated MWVC.cc
// Purpose: This code finds the minimum weighted vertex cover in a graph by 
// using brute force search. The algorithm is split into threads using c++ 11
// threads and the future class.
// Original Author: David Juedes
// Update Author: Tyler Cline
// Ohio University 2016

#include <iostream>
#include <vector>
#include <set>
#include <list>
#include <sstream>
#include <thread>
#include <future>
using namespace std;

//Number of threads for the program using the hardware concurrency function
static const int num_threads = std::thread::hardware_concurrency();
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

bool min_weighted_vc(vector<list<int> > &adj_list,
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
    if (isVertexCover(adj_list, t) ){
      double w=0;
      for (set<int>::iterator p=t.begin();p!=t.end();++p) {
        w+=weights[*p];
      }
      if (w<prev_min) { prev_min = w; min_set = t;}
    }
      }
  return true;
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
  //This marks to beginning of the edited code. It utilizes the num_threads value 
  //which was derived from the hardware_concurrency thread function
    //Declare an array of future booleans
     future<bool> threads[num_threads];
    //Iterate through the array of threads and initialize each spot to the function
  //which now returns a boolean. each thread will run fully asynchronous
    for(int i = 0; i < num_threads; ++i){
      threads[i] = async(launch::async, min_weighted_vc, ref(adj_list), ref(weights), ref(min_set), ref(prev_min));
    }
    //Declare a second array t2 which holds bool values
    bool t1[num_threads];
    //A loop to iterate through the future array to use the .get() member function
  //to wait for each thread to finish getting the values
    for(int i = 0; i < num_threads; ++i){
      t1[i] = threads[i].get();
    }
    // min_weighted_vc(adj_list,weights,min_set,prev_min);
  cout << "Weight of minimum VC = " << prev_min << endl;
  cout << "Best Set = " << endl;
  for (set<int>::iterator p = min_set.begin();
       p!=min_set.end();++p) {
    cout <<*p << " weight = " << weights[*p] << endl;
  }
  cout << endl;
}

