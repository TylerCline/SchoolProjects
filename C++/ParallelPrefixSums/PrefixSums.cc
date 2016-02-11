
//**************************************************
//PrefixSums.cc
//Tyler Cline
//Ohio University 2016
//NOTE: It appears there are race conditions while using stl
//      and using critical sections don't seem to alleviate
//      the issue.
//**************************************************
#include "PrefixSums.h"
#include <iostream>
#include <omp.h>

vector<int> PrefixSums::prefix_sums(vector<int> &A) {
 
//Declaring two arrays, as specified in the algorithm given in class. One to hold the
//final values and one to hold calculated values. Each vector is off the original 
//size of A
 vector<int> y(A.size());
 vector<int> S(A.size());

//since I used iteration for the entire algorithm, I am doing the whole thing in 
//parallel and specifying critical sections.
 #pragma omp parallel
 {
  //Setting up loop variables to iterate properly
  size_t N = A.size();
  int ithread = omp_get_thread_num();
  int nthreads = omp_get_num_threads();
  int start = ithread*N/nthreads;
  int finish = (ithread+1)*N/nthreads;
  
  //initializing the first element of y
  y[0] = 0;

  float sum = 0;
 
  for(int i = start; i < finish; i++)
  {
       #pragma omp critical
       {
  	sum += A[i];
  	S[i] = sum;
       }
  }
  //
  y[ithread+1] = sum;

  #pragma omp barrier
  int off = 0;

  for(int i=0; i < (ithread+1); i++)
  {
        #pragma omp critical
  	off += y[i];
  }

  for(int i=start; i<finish; i++)
  {
     #pragma omp critical
     S[i] += off;
  }
}

return S;

}
