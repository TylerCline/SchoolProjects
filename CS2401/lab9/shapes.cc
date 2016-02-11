#include<iostream>
#include<cmath>
#include"shapes.h"
using namespace std;


Shape::Shape()
{thickness=0; 
 cost_pcu=0;}


void Shape::input()
   {cout<<"enter the thickness and cost per unit--> "; 
    cin>>thickness>>cost_pcu;}


double Shape::cost()
{return thickness*cost_pcu*area();}


//Circles
Circle::Circle() 
{ radius=0;}

void Circle::input()
{     Shape::input();

 cout<<"enter the radius of the circle"<<endl;
      cin>>radius;}

double Circle::area()
   {    
    return M_PI*radius*radius;}



//rectangles
Rectangle::Rectangle()
{
 length=0; 
 width=0;
}

             
void Rectangle::input()
{    Shape::input();
 cout<<"enter the length"<<endl<<"length-->";
 cin>>length;
 cout<<"width-->";
 cin>>width;}

double Rectangle::area()
{       
return length*width;}




//trapezoid
Trapezoid::Trapezoid()
{base1=0; 
 base2=0; 
 height=0;}
        
void Trapezoid::input()
{     Shape::input();
 cout<<"enter in base 1 and 2 --> "; 
 cin>>base1>>base2;
 cout<<"enter the height --> "; 
 cin>>height;}
      
double Trapezoid::area()
{      
return height*(base1+base2)/2.0;}
 

