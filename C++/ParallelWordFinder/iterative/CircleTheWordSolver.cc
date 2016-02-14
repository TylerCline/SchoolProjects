//*********************************************************
//CircleTheWordSolver.cc
//Author: Tyler Cline
//Purpose: Iterative version that solves a circle the word
//         puzzle in O(w*n^2*w') where w = Size(wordList),
//         n = Size(puzzle), and w' = Size(wordlist[i])
//*********************************************************

#include "CircleTheWordSolver.h"
#include <vector>
#include <string>
#include <algorithm>
#include <iostream>

vector<pair<int, int> > CircleTheWordSolver::word_locations(
         vector<vector<char> > &puzzle, 
         vector<string> &wordlist)
{ 
  vector <pair<int, int > > loc;
  int cntr = puzzle[0].size();
  int wordl = wordlist.size();
  string word;
  int trueCount = 0;
  bool found = true; 

  //Outer for loop to search the wordlist for the 
  for(int k = 0; k < wordl; k++)
    { 
      found = false;
      word = wordlist[k];
      //Inner loops to find coordinates
      for(int x = 0; x < cntr; x++)
	{ 
	  for(int y = 0; y < cntr; y++)
	    { 
	      //If the first character matches, check 8 derections. If the word is found, then found is set to true
	      //if found is already true, the loops will not be executed, making the program more efficient. 
	      if (puzzle[x][y] == word[0])
		{
                 //*****************Verticle and horizontal Cecking*************//
                 //Check down
		  if(found = false)
                 {
		  for(int i = 0; i < word.size(); i++)
                    {
			if((y+i) < cntr)
                        {
			   if(puzzle[x][y+i] == word[i])
			   {   
                               
                               trueCount++;

			       if(trueCount == word.size()){
                                
				  found = true;
			          loc.push_back(make_pair(x, y));
                                 
                              }
                            
			   }
			}
                    }
                  }
		   trueCount = 0;

		   //check up
		   if(found == false)
		     {
		   for(int i = 0; i < word.size(); i++)
                    {
			if((y-i) > 0)
                        {
			   if(puzzle[x][y-i] == word[i])
			   {
                               trueCount++;

			       if(trueCount == word.size()){
				found = true;
			          loc.push_back(make_pair(x, y));
                                
                               }
			     
			   }
			}
                    }
		     }
		trueCount = 0;
		   //check right
		   if (found == false)
                  {
		   for(int i = 0; i < word.size(); i++)
                    {   
			if((x+i) < cntr)
                        {
			   if(puzzle[x+i][y] == word[i])
			   {
                               trueCount++;

			       if(trueCount == word.size()){
				  found = true;
			          loc.push_back(make_pair(x, y));
                                
			       }
			   }
			}
                    }
		  }
		   trueCount = 0;

		  //check left
		   if(found == false)
                  {
		   for(int i = 0; i < word.size(); i++)
                    {
			if((x-i) > 0)
                        {
			   if(puzzle[x-i][y] == word[i])
			   {
                               trueCount++;

			       if(trueCount == word.size()){
                                 found = true;
			          loc.push_back(make_pair(x, y));
                                
			       }	  
			   }
			}
                    }
		  }
                  trueCount = 0;


	      if(found == false)
               {
		for(int i = 0; i < word.size(); i++)
                    {
			if((x+i) < cntr && (y+i) < cntr)
                        {
			   if(puzzle[x+i][y+i] == word[i])
			   {
                               trueCount++;

			       if(trueCount == word.size()){
                                 found = true;
			          loc.push_back(make_pair(x, y));
			     
                               }
			   }
			}
                    }
	       }
	      trueCount = 0;

              if(found == false)
		{
		for(int i = 0; i < word.size(); i++)
                    {
			if((x+i) < cntr && (y-i) > 0)
                        {
			   if(puzzle[x+i][y-i] == word[i])
			   {
                               trueCount++;

			       if(trueCount == word.size()){
                                  found = true;
			          loc.push_back(make_pair(x, y));
                                 
                               }
                           }
			     
			}
                    }
		}
		   trueCount = 0;
		   if(found == false)
		     {
		for(int i = 0; i < word.size(); i++)
                    {
			if((x-i) > 0 && (y-i) > 0)
                        {
			   if(puzzle[x-i][y-i] == word[i])
			   {
                               trueCount++;

			       if(trueCount == word.size()){
                                  found = true;
			          loc.push_back(make_pair(x, y));
                               
                               }
			     
			   }
			}
                    }
		     }
		   trueCount = 0;
		   if(found == false)
		     {
		for(int i = 0; i < word.size(); i++)
                    {
			if((x-i) > 0 && (y+i) < cntr)
                        {
			   if(puzzle[x-i][y+i] == word[i])
			   {
                               trueCount++;

			       if(trueCount == word.size()){
                                  found = true;
			          loc.push_back(make_pair(x, y));
                               
                               }
			   }
			}
                    }
		     }
		 trueCount = 0;
		 //one, or more loops execute, and find the answer, the inner loop breaks, so that the next word can be loaded.
		 if(found == true) break;
		}
	    }
          //Once again, if the word was found, this will break the x coordinate loop, so that the next word can be loaded. 
          if(found == true) break;
	}
      //If all of the loops have exectuted, and the entire matrix is exhausted, and found is still false, the word does not exist,
      //Therefore, push back -1, -1
      if(found == false)
        loc.push_back(make_pair(-1,-1));
    }
return loc;
}
