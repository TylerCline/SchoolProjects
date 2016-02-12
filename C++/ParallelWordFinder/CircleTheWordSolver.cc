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

  for(int k = 0; k < wordl; k++)
    { found = false;
      word = wordlist[k];
      for(int x = 0; x < cntr; x++)
	{ 
	  for(int y = 0; y < cntr; y++)
	    { 
	      if (puzzle[x][y] == word[0])
		{
                 //*****************Verticle and horizontal Cecking*************//
                 //Check down
		  for(int i = 0; i < word.size(); i++)
                    {
			if((y+i) < cntr)
                        {
			   if(puzzle[x][y+i] == word[i])
			   {
                               trueCount++;

			       if(trueCount == word.size()){
				  found = true;
			          loc.push_back(make_pair(x, y));}
                            
			   }
			}
                    }
		   trueCount = 0;

		   //check up
		   for(int i = 0; i < word.size(); i++)
                    {
			if((y-i) > 0)
                        {
			   if(puzzle[x][y-i] == word[i])
			   {
                               trueCount++;

			       if(trueCount == word.size()){
				found = true;
			          loc.push_back(make_pair(x, y));}
			     
			   }
			}
                    }
		
		   //check right
		   for(int i = 0; i < word.size(); i++)
                    {   
			if((x+i) < cntr)
                        {
			   if(puzzle[x+i][y] == word[i])
			   {
                               trueCount++;

			       if(trueCount == word.size()){
				  found = true;
			          loc.push_back(make_pair(x, y));}
			    
			   }
			}
                    }
		   trueCount = 0;

		  //check left
		   for(int i = 0; i < word.size(); i++)
                    {
			if((x-i) > 0)
                        {
			   if(puzzle[x-i][y] == word[i])
			   {
                               trueCount++;

			       if(trueCount == word.size()){
                                 found = true;
			          loc.push_back(make_pair(x, y));}
			  
			   }
			}
                    }
		   trueCount = 0;


		
		for(int i = 0; i < word.size(); i++)
                    {
			if((x+i) < cntr && (y+i) < cntr)
                        {
			   if(puzzle[x+i][y+i] == word[i])
			   {
                               trueCount++;

			       if(trueCount == word.size()){
                                 found = true;
			          loc.push_back(make_pair(x, y));}
			   }
			}
                    }
		   trueCount = 0;

		for(int i = 0; i < word.size(); i++)
                    {
			if((x+i) < cntr && (y-i) > 0)
                        {
			   if(puzzle[x+i][y-i] == word[i])
			   {
                               trueCount++;

			       if(trueCount == word.size()){
                                  found = true;
			          loc.push_back(make_pair(x, y));}
                           }
			     
			}
                    }
		   trueCount = 0;
		
		for(int i = 0; i < word.size(); i++)
                    {
			if((x-i) > 0 && (y-i) > 0)
                        {
			   if(puzzle[x-i][y-i] == word[i])
			   {
                               trueCount++;

			       if(trueCount == word.size()){
                                  found = true;
			          loc.push_back(make_pair(x, y));}
			     
			   }
			}
                    }
		   trueCount = 0;

		for(int i = 0; i < word.size(); i++)
                    {
			if((x-i) > 0 && (y+i) < cntr)
                        {
			   if(puzzle[x-i][y+i] == word[i])
			   {
                               trueCount++;

			       if(trueCount == word.size()){
                                  found = true;
			          loc.push_back(make_pair(x, y));}
			   }
			}
                    }
		 trueCount = 0;
		}	
	    }
	}
      if(found == false)
        loc.push_back(make_pair(-1,-1));
    }
return loc;
}
