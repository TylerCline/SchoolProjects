#include<iostream>
#include<string>
#include"trucks.h"
using namespace std;

roads::roads()
{
 priority = 0;
 x = 0;
 y = 0;
 miles = 0;

}

istream& operator >>(istream& in, roads& c)
{
 c.input(in);
 return in;
}

void roads::input(istream& in)
{
 in>>priority;
 getline(in, name, '(');
 in>>x;
 while(in.peek()==',')
 {
     in.ignore();
 }
 in>>y;
 while(in.peek()==')'){
    in.ignore();
 };
 in>>miles;

}
void roads::operator =(roads& c)
{
 priority = c.priority;
 x = c.x;
 y = c.y;
 miles = c.miles;
 name  = c.name;
}


void roads::output(std::ostream& outs)const
{
 outs<<"Road name: "<< name << endl;
}
