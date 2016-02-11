//******************************************
//implementation file for the vehicle class
//Tyler Cline
//Ohio University 2014
//******************************************

#include<iostream>
#include"vehicle.h"
#include<string>
using namespace std;

vehicle::vehicle()
{
    year=0;
}

//****************************
//Accesor Functions
//****************************

string vehicle::owner()
{
    return(car_owner);
}

string vehicle::get_tag()
{
    return(license);

}

int vehicle::get_year()
{
    return(year);

}

string vehicle::get_make()
{
    return(make);
}

string vehicle::get_model()
{
    return(model);
}

//**************************************
//Mutator Functions
//**************************************

void vehicle::set_owner(string& setname)
{   cout<<"Enter in the driver's name --> ";
    if(cin.peek()=='\n')cin.ignore();
    getline(cin, setname);
    car_owner=setname;
}


void vehicle::set_tag(string& setlicense)
{
    cout<<"Enter in the vehicle's license number --> ";
    getline(cin,setlicense);
    license=setlicense;
}

void vehicle::set_year(int& setyear)
{
    cout<<"Enter in vehicle year --> ";
    cin>>setyear;
    year=setyear;
}

void vehicle::set_make(string& setmake)
{
    cout<<"Enter in the vehicle's make --> ";
    getline(cin, setmake);
    make=setmake;
}

void vehicle::set_model(string& setmodel)
{
    cout<<"Enter in the vehicle model --> ";
    getline(cin, setmodel);
    model=setmodel;
}

istream& operator>>(istream& ins, vehicle& info )
{   cout << "Enter the car owner "<<endl;
      if(cin.peek()=='\n')cin.ignore();
      getline(ins, info.car_owner);
    cout << "Enter tag "<<endl;
      getline(ins, info.license);
    cout << "Enter year "<<endl;
      ins >> info.year;
    cout << "Enter make "<<endl;
      if(cin.peek()=='\n')cin.ignore();
      getline(ins, info.make);
    cout << "Enter model "<<endl;
      getline(ins, info.model);

    return(ins);
}

ostream& operator << (std::ostream& outs, vehicle& car_info)
{
    outs <<"Car Owner: "<< car_info.car_owner<<endl;
    outs <<"Car tag: "<< car_info.license<<endl;
    outs <<"Year: "<< car_info.year<<endl;
    outs <<"Car Make: "<<car_info.make<<endl;
    outs <<"Car Model: "<<car_info.model<<endl;
    return(outs);

}
