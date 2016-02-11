#include<iostream>
#include<list>
#include<string>
#include<fstream>
#include"transportation.h"
using namespace std;

int table();

int main()
{
int choice;
ifstream ifs;
string words;
list<transportation*> mytransport;
list<transportation*>::iterator i;
transportation *tmp;


   ifs.open("trans.dat");
    if(ifs.fail()){
            cout<<"no file input"<<endl;
              return 1;
              }

    while(ifs>>words)
    {
      if(ifs.eof()) break;

      if(words=="Stratofortress")
        {
         tmp = new stratofortress;
         tmp->input(ifs);
         mytransport.push_back(tmp);
        }
      else if(words=="Cruise")
        {
         tmp = new cruise_ship;
         tmp->input(ifs);
         mytransport.push_back(tmp);
        }
      else if(words=="Semi")
        {
         tmp = new semi_truck;
         tmp->input(ifs);
         mytransport.push_back(tmp);
        }
      else if(words=="Kayak")
        {
         tmp = new kayak;
         tmp->input(ifs);
         mytransport.push_back(tmp);
        }
      else if(words=="Zeppelin")
        {
         tmp = new zeppelin;
         tmp->input(ifs);
         mytransport.push_back(tmp);
        }
      else if(words=="Destroyer")
        {
         tmp = new destroyer;
         tmp->input(ifs);
         mytransport.push_back(tmp);
        }
        }
      ifs.close();


cout<<"Welcome Universal transportation!"<<endl<<"select a mode of transportation to customize"<<endl;

do{
   choice=table();

   switch(choice){

       case 1:
         tmp = new stratofortress;
         cout<<"YOU CHOSE STRATOFORTRESS! "<<endl;
         tmp->input(cin);
         mytransport.push_back(tmp);

           break;

       case 2:
         tmp = new cruise_ship;
         cout<<"YOU CHOSE CRUISE SHIP!"<<endl;
         tmp->input(cin);
         mytransport.push_back(tmp);

           break;

       case 3:
         tmp = new semi_truck;
         cout<<"YOU CHOSE SEMI TRUCK!"<<endl;
         tmp->input(cin);
         mytransport.push_back(tmp);
           break;

       case 4:
         tmp = new kayak;
         cout<<"YOU CHOSE KAYAK!"<<endl;
         tmp->input(cin);
         mytransport.push_back(tmp);
           break;

       case 5:
         tmp = new zeppelin;
         cout<<"YOU CHOSE ZEPPELIN!"<<endl;
         tmp->input(cin);
         mytransport.push_back(tmp);

           break;

       case 6:

         tmp = new destroyer;
         cout<<"YOU CHOSE DESTROYER!"<<endl;
         tmp->input(cin);
         mytransport.push_back(tmp);

           break;

       case 7:

         i = mytransport.begin();
           while(i != mytransport.end())
            {
             (*i)->output(cout);
              ++i;
            }

           break;

       case 8:
        cout<<"Enjoy your new transport! "<<endl;
           break;

       default:
        cout<<"Not a menu Option "<<endl;
           break;
}
}while(choice != 8);


	ofstream ofs;
	ofs.open("trans.dat");
	if(!ofs.fail()){
            i=mytransport.begin();
            while(i != mytransport.end())
                  {(*i)->output(ofs);
                   ++i;
                  }
                       ofs.close();
                       }

return 0;
}


int table(){
    int ans;
    cout<<"1) Stratofortress \n";
    cout<<"2) Cruise Ships \n";
    cout<<"3) Semi Trucks\n";
    cout<<"4) Kayaks\n";
    cout<<"5) Zeppelins\n";
    cout<<"6) Destroyers\n";
    cout<<"7) Display All\n";
    cout<<"8) Exit\n";
    cin>>ans;
    return ans;
}
