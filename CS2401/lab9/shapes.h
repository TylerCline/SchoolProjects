//*******************************************************
//Implementaion Of inheritence
//Tyler Cline
//*******************************************************

#include<iostream>

class Shape
{
      public:
             Shape();
             virtual void input();
             virtual double area()=0;
             double cost();

      private:
              double thickness;
              double cost_pcu;

};


class Circle:public Shape
{
      public:
             Circle();
             void input();
             double area();
      private:
             double radius;
};

class Rectangle:public Shape
{
      public:
             Rectangle();
             void input();
             double area();
      private:
              double length, width;
};

class Trapezoid:public Shape
{
      public:
             Trapezoid();
             void input();
             double area();
 

      private:
             double height, base1, base2;
};







