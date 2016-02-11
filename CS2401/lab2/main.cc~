//Main function file
//**********************
//Main Function 
//Tyler Cline 2014
//Ohio University
//**********************

#include "numlist.h"
#include <iostream>
#include <fstream>
#include <ostream>

using namespace std;

int main()
{
 ifstream fin;
 NumList mynum;
 string filename;
 int temp;

 cout << "Enter Filename"<<endl;
 cin >> filename;

  fin.open(filename.c_str());
    if(fin.fail())
       {  cout<<"Input file failed to open. \n";
          return -1;}
  mynum.load_from_file(fin);
  fin.close();

  mynum.see_all();

  cout << "Enter three numbers to add to the list "<<endl;
  cin >> temp;
  mynum.insert(temp);
  cin >> temp; 
  mynum.insert(temp);
  cin >> temp;
  mynum.insert(temp);
  
  mynum.b_sort();

  mynum.see_all();
  mynum.b_sort();

  int locate = filename.find(".");
  filename.insert(locate, "sorted");
  
  ofstream fout(filename.c_str());
  mynum.save_to_file(fout);
  fout.close();


return (0);
}
