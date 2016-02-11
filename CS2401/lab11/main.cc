#include<iostream>
using namespace std;

void counting(int num);

int main(){
int num1;


cout<<"Enter a positive number ";
cin>>num1;
cout<<"Even numbers counting to there"<<endl;
counting(num1);

return 0;
}


void counting(int num)
{
 if(num<0)
    return;
 else if(num%2==1)
    { 
     counting(num-1);} 
 else{   
         counting(num-1);
         cout<<num<<endl;
}
}
      
