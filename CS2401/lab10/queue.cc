#include<iostream>
#include<string>
#include"queue.h"
using namespace std;

void chore::input()
{
 cout<<"Enter the Chore "<<endl;
 cin>>description;
 cout<<"Enter the priority level "<<endl;
 cin>>priority;
 
}

void chore::output()const
{
 cout<<"chore: "<<description<<endl;
 cout<<"Priority level: "<<priority<<endl;
}
