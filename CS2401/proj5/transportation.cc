#include<iostream>
#include<string>
#include"transportation.h"
using namespace std;

stratofortress::stratofortress()
{
    ammunition_mm=0;
    crew_capacity=0;
}

cruise_ship::cruise_ship()
{
    approx_bouyancy=0;
    approx_knots=0;
}

semi_truck::semi_truck()
{
  trailer_size=0;
  num_of_gears=0;
}

kayak::kayak()
{   thickness=0;
    weight_limit=0;
    length=0;
}

zeppelin::zeppelin()
{
    num_of_bags=0;
    cabin_occupancy=0;
}

destroyer::destroyer()
{
    bouyancy=0;
    num_of_barracks=0;
}
void stratofortress::input(istream& in)
{
    if(in==cin)
    {
        cout<<"enter in the propeller engine type ->";
         in>>propeller_engine_type;
        cout<<"enter in the type of armaments for the aircraft->";
         in>>armaments;
        cout<<"enter in the elevation capable of traversing->";
         in>>capable_elevation;
        cout<<"enter in the size of ammunition->";
         in>>ammunition_mm;
        cout<<"enter in the crew capacity-> ";
         in>>crew_capacity;
    }
    else
    {
        in>>propeller_engine_type;
        in>>armaments;
        in>>capable_elevation;
        in>>ammunition_mm>>crew_capacity;
    }
}

void stratofortress::output(ostream& out)
{  if(out==cout){
    out<<"Stratofortress "<<endl;
    out<<"Propeller Type: "<<propeller_engine_type<<endl;
    out<<"Weapon Type: "<<armaments<<endl;
    out<<"Approximate Capable Elevation: "<<capable_elevation<<endl;
    out<<"Size of ammunition: "<<ammunition_mm<<endl;
    out<<"Approximate crew capacity: "<<crew_capacity<<endl<<endl;}
  
   else{
    out<<"Stratofortress "<<endl;
    out<<propeller_engine_type<<endl;
    out<<armaments<<endl;
    out<<capable_elevation<<endl;
    out<<ammunition_mm<<endl;
    out<<crew_capacity<<endl<<endl;
}
}

void cruise_ship::input(istream& in)
{
    if(in==cin)
    {
        cout<<"Enter the name of the Vessel-> ";
         in>>name;
        cout<<"Enter an activity to participate in on the vessel->";
         in>>activities;
        cout<<"Enter in the approximate Bouyancy->";
         in>>approx_bouyancy;
        cout<<"Enter in the approximate Knots that the ship can travel-> ";
         in>>approx_knots;
    }
    else
    {
        in>>name;
        in>>activities;
        in>>approx_bouyancy>>approx_knots;
    }
}

void cruise_ship::output(ostream& out)
{  if(out==cout){
    out<<"Cruise Ship "<<endl;
    out<<"Vessel Name "<<name<<endl;
    out<<"Activities "<<activities<<endl;
    out<<"Approximate Bouyancy "<<approx_bouyancy<<endl;
    out<<"Approximate Knots "<<approx_knots<<endl<<endl;}
  else{
    out<<"Cruise"<<endl;
    out<<name<<endl;
    out<<activities<<endl;
    out<<approx_bouyancy<<endl;
    out<<approx_knots<<endl<<endl;
      }
}

void semi_truck::input(istream& in)
{
    if(in==cin)
    {cout<<"Enter the Truck Make-> ";
     in>>make;
    cout<<"Enter the truck model-> ";
     in>>model;
    cout<<"Enter the Company Name to Print on the truck-> ";
     in>>company;
    cout<<"Enter in the size of the trailer needed-> ";
     in>>trailer_size;
    cout<<"Enter the number of gears-> ";
     in>>num_of_gears;}

    else
    {
        in>>make;
        in>>model;
        in>>company;
        in>>trailer_size>>num_of_gears;
    }
}

void semi_truck::output(ostream& out)
{   
   if(out==cout){
    out<<"Semi Truck"<<endl;
    out<<"Make: "<<make<<endl;
    out<<"Model: "<<model<<endl;
    out<<"Company: "<<company<<endl;
    out<<"Trailer size "<<trailer_size<<endl;
    out<<"Number of Transmission Gears: "<<num_of_gears<<endl<<endl;}

  else{
    out<<"Semi"<<endl;
    out<<make<<endl;
    out<<model<<endl;
    out<<company<<endl;
    out<<trailer_size<<endl;
    out<<num_of_gears<<endl;}
}

void kayak::input(istream& in)
{
    if(in==cin)
    {
        cout<<"Enter the kayak type->";
         in>>kayak_type;
        cout<<"Enter the plastic thickness-> ";
         in>>thickness;
        cout<<"Enter a weight limit-> ";
         in>>weight_limit;
        cout<<"Enter the length-> ";
         in>>length;
    }
    else
    {
        getline(in, kayak_type);
        in>>thickness>>weight_limit>>length;
    }
}

void kayak::output(ostream& out)
{  if(out==cout){
    out<<"Kayak"<<endl;
    out<<"Kayak Type: "<<kayak_type<<endl;
    out<<"Plastic thickness: "<<thickness<<endl;
    out<<"Weight Limit: "<<weight_limit<<endl;
    out<<"Length: "<<length<<endl<<endl;}

  else{
    out<<"Kayak"<<endl;
    out<<kayak_type<<endl;
    out<<thickness<<endl;
    out<<weight_limit<<endl;
    out<<length<<endl<<endl;
}
}

void zeppelin::input(istream& in)
{
    if(in==cin)
    {
        cout<<"Enter in the gas Type-> ";
         in>>gas_type;
        cout<<"Enter in the Gas bag material Type-> ";
         in>>bag_material_type;
        cout<<"Enter in the Number of Bags-> ";
         in>>num_of_bags;
        cout<<"Enter in the Max Cabin Occupancy-> ";
         in>>cabin_occupancy;
    }
    else{
        in>>gas_type;
        in>>bag_material_type;
        in>>num_of_bags;
        in>>cabin_occupancy;
        }
}

void zeppelin::output(ostream& out)
{  if(out==cout){
    out<<"Zeppelin"<<endl;
    out<<"Gas Type: "<<gas_type<<endl;
    out<<"Bag material Type: "<<bag_material_type<<endl;
    out<<"Number of Bags: "<<num_of_bags<<endl;
    out<<"Max Occupancy: "<<cabin_occupancy<<endl<<endl;
}
   else{
    out<<"Zeppelin"<<endl;
    out<<gas_type<<endl;
    out<<bag_material_type<<endl;
    out<<num_of_bags<<endl;
    out<<cabin_occupancy<<endl;}

}
void destroyer::input(istream& in)
{
    if(in==cin)
    {
        cout<<"Enter in the Type of Destroyer ";
         in>>type;
        cout<<"Enter in the type of weapons-> ";
         in>>weapons;
        cout<<"Enter in Propulsion engine Type-> ";
         in>>propulsion;
        cout<<"Enter in the approximate bouyancy-> ";
         in>>bouyancy;
        cout<<"Enter in the number of Barracks-> ";
         in>>num_of_barracks;
    }
    else{
        in>>type;
        in>>weapons;
        in>>propulsion;
        in>>bouyancy>>num_of_barracks;}
}

void destroyer::output(ostream& out)
{   

    if(out==cout){
     out<<"Destroyer"<<endl;
     out<<"Type of Destroyer: "<<type<<endl;
     out<<"Type of armaments: "<<weapons<<endl;
     out<<"Type of engines: "<<propulsion<<endl;
     out<<"Approximate bouyancy: "<<bouyancy<<endl;
     out<<"Number of barracks: "<<num_of_barracks<<endl<<endl;}

    else{
    out<<"Destroyer"<<endl;
    out<<type<<endl;
    out<<weapons<<endl;
    out<<propulsion<<endl;
    out<<bouyancy<<endl;
    out<<num_of_barracks<<endl;}
}




