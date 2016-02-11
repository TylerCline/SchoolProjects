//*******************************
//Vehicle class header file
//Tyler CLine
//Ohio University 2014
//*******************************

#include<iostream>
#ifndef VEHICLE_H
#define VEHICLE_H

class vehicle{
 public:
     vehicle();
     std::string owner();
     std::string get_tag();
     int get_year();
     std::string get_make();
     std::string get_model();

     void set_tag(std::string& setlicense);
     void set_owner(std::string& setowner);
     void set_year(int& setyear);
     void set_make(std::string& setmake);
     void set_model(std::string& setmodel);

     friend std::istream& operator >> (std::istream& ins, vehicle& info);
     friend std::ostream& operator << (std::ostream& outs, vehicle& car_info);
 private:
      std::string car_owner;
      std::string license;
      int year;
      std::string make;
      std::string model;

};
#endif
