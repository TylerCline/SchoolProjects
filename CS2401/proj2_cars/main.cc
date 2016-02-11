/*********************************************************************
     Shady Clem's In-Town parking has decided to use the BMV class to
     develop their own application for tracking the cars that they park
     in their lot in downtown Chicago. (They continue to deny the claims
     that they have links to organized crime, and certain well-know car
     theft rings.

	You care to write classes (both the .h and the .cc files) that
     will allow this application to work.

	Tyler Cline			Ohio University - EECS
	Fall 2014
*********************************************************************/
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>
#include <ctime>
#include "vehicle.h"
#include "bmv.h"

using namespace std;
/***********************************************************
   The menu function displays a menu and returns the user's choice.
************************************************************/
int menu();


int main(){
     srand(time(NULL));
     bmv cars;
     vehicle tmp;
     ifstream ifs;
     ofstream ofs;
     int choice;
     string tag;

// Shady Clems are keeping their cars in this data base
   /* ifs.open("shady.dat");
    if(!ifs.fail()){
	cars.load_from_file(ifs);
	ifs.close();
     }*/


    do{
	   choice = menu();
	switch(choice){
	    case 1:
		       cin>>tmp;
               for(cars.start();cars.is_item() && cars.current().owner()< tmp.owner();cars.advance());
               // do nothing in this loop

		       if(cars.is_item())
		          cars.insert(tmp);
		       else
		          cars.attach(tmp);
		 break;

	    case 2:   // search by license number
		       cin>>tag;  // note that license number is a string
		       cars.show_item(tag);
		 break;

	    case 3:  // removing a vehicle that has turned up missing
		       cin>>tag;
               for(cars.start(); cars.current().get_tag() != tag; cars.advance());
                //again a loop that just advances the iterator

		       if(cars.is_item())
		          cars.remove_current();
		 break;

        case 4:  // picking a target for tonight's operation
                cars.random_car();
		 break;


        case 5: //looking at all of the cars
		        for(cars.start(); cars.is_item(); cars.advance())
		        cout << cars.current();
		 break;


        case 6: {  // making the copy of the database for Sid
		        bmv copy(cars);
                int i;
		        for(i = 0, copy.start();i < copy.size()/2; i++,copy.advance());
		         // again just walking into the list

		        if(copy.is_item())
                  {
		            cout<<"This record to be cleared:\n"<<endl;
			        cout<<copy.current();
                    copy.remove_current();
		          }
                cout<<"Now printing the altered copy:\n";
		        for(copy.start();copy.is_item(); copy.advance())cout<<copy.current();
		 break;
		}   // copy goes out of scope here
        case 7:
		        cout<<"Thank you for parking at Shady Clem's.\n";
		 break;

        default:
                cout<<"Not a menu option.\n";
		 break;
	}  // bottom of the switch
   }while(choice != 7);

	ofs.open("shady.dat");
	if(!ofs.fail())
	   cars.save_to_file(ofs);
	ofs.close();

return (0);
}

int menu(){
    int ans;
    cout<<"Welcome to Shady Clem's database. Please choose an option:\n";
    cout<<"1) \n";
    cout<<"2) \n";
    cout<<"3) \n";
    cout<<"4) \n";
    cout<<"5) \n";
    cout<<"6) \n";
    cout<<"7) \n";
    cin>>ans;
return ans;
}
