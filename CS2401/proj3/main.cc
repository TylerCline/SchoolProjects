//************************************
//Main file for linked list container
//Tyler CLine
//ohio university 2014
//************************************

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>
#include "LList.h"
#include "course.h"

using namespace std;

int menu();

int main(){

     llist c;
     course tmp;
     string filename;
     ifstream inputf;
     int choice;
     string target;


   // cout<<"Enter Username"<<endl;
   // getline(cin, filename);
    inputf.open("Tyler.dat");
     if(!inputf.fail())
     {
	  c.load_from_file(inputf);
	  inputf.close();
	//  cout<<"Hello "<<filename<<"!"<<endl<<endl;
     }


    do{
	   choice = menu();
	switch(choice){
	    case 1:
		      c.add_class();
		      cout<<endl;
		 break;

	    case 2:
              c.show_all();
              cout<<endl;
		 break;

	    case 3:
	           cout<<"Enter In a course to Remove "<<endl;
		       cin>>target;

		       for(int i =0; i<target.length(); ++i)
	              target[i] = toupper(target[i]);

               c.remove_course(target);
               cout<<endl;

		 break;

        case 4:
               c.gpa();
               cout<<endl;
		 break;


        case 5:
               c.hours_taken();
		 break;

        case 6:{
                 string y;
                 llist copy(c);
                 copy.show_all();
                 cout << "Enter a course to remove "<<endl;
                 cin >> y;
                 copy.remove_course(y);

         break;
        }
        case 7:
               cout<<"Goodbye "<<endl<<endl;
               cout<<"                     (....data saved)"<<endl<<endl;
         break;


        default:
                cout<<"Not a menu option.\n";
		 break;
	}  // bottom of the switch
   }while(choice != 7);

	ofstream ofs;
	ofs.open("Tyler.dat");
	if(!ofs.fail())
        c.save_to_file(ofs);
	 ofs.close();

return (0);
}

int menu(){
    int ans;
    cout<<endl<<endl;
    cout<<"Please choose an option: "<<endl;
    cout<<"1: Add a class "<<endl;
    cout<<"2: Show all classes "<<endl;
    cout<<"3: Drop a course "<<endl;
    cout<<"4: Calculate GPA "<<endl;
    cout<<"5: Total Hours Taken"<<endl;
    cout<<"6: Make a copy"<<endl;
    cout<<"7: Quit "<<endl;
    cin>>ans;
    cout<<endl;
return ans;
}