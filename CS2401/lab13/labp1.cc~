// home1.cc
// Written by DWJ on 1/26/2013
// This code reads in a file containing two n x n matrices,
// multiplies the matrices, and produces the output.

#include <vector>
#include <iostream>
#include <fstream>
using namespace std;
void mult(vector<vector<int> > &A, vector<vector<int> > & B,
	  vector<vector<int> > &C) {
  
  int n = A.size();
  #pragma omp parallel for
  for (int i=0;i<n;i++) {
     for (int j=0;j<n;j++) {
      int sum=0;
      for (int k=0;k<n;k++) {
	sum+=A[i][k]*B[k][j];
      }
      C[i][j] = sum;
    }
  }
}

int main() {
  int n;
  ifstream ins;
  //ins.open("900.dat");
  cin >> n;
  vector<vector<int> > A;
  vector<vector<int> > B;
  vector<vector<int> > C;
  A.resize(n);
  B.resize(n);
  C.resize(n);
  for (int i=0;i<n;i++) {
    A[i].resize(n);
    B[i].resize(n);
    C[i].resize(n);
  }
  for (int i=0;i<n;i++) {
    for (int j=0;j<n;j++) {
      cin >> A[i][j];
    }
  }
  for (int i=0;i<n;i++) {
    for (int j=0;j<n;j++) {
      cin >> B[i][j];
    }
  }
  mult(A,B,C);
  long long sum=0;
  for (int i=0;i<n;i++) {
    for (int j=0;j<n;j++) {
      sum+=C[i][j];
    }
  }
ins.close();
  cout << "The sum of the entries in C is " << sum << endl;
}		
