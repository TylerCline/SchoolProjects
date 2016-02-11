#include <iostream>
#include <cstdlib>
#include <cassert>
#include "PrefixSums.h"

using namespace std;

int main() {

  vector<int> A;
  vector<int> P;

  while (!cin.fail()) {
    int x;
    cin >> x;
    if (!cin.fail()) {
      A.push_back(x);
    }
  }
  
  
  PrefixSums obj;
  P = obj.prefix_sums(A);
 

  assert(A.size()==P.size());


  for (size_t i=0;i<P.size();i++) {
    cout << "Prefix Sum " << i << " = " << P[i] << endl;
  }
}
