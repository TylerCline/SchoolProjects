#include<iostream>
using namespace std;

int main()
{
 int *ptr;

 ptr = new int;
 
 cout<<ptr<<endl;
 cout<<&ptr<<endl;
  ptr++;

for(int j=0; j <=1099; j++){
--(ptr);
cout<<*ptr<<"is stored at"<<ptr<<endl;
}


 delete ptr;

return(0);
}
