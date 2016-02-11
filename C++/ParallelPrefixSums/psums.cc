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
  
  //initializing the first element of y
  y[0] = 0;
 
  for(int i = 0; i < N/2; i++)
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
