#include <iostream>
# include "MyTime.h"
using namespace std;

int main()
{
MyTime t1, t2;
 int scalar;

cout << "Enter 2 Valid Times and a scalar";
cout << "--->";
  cin >> t1; 

cout << "--->";
  cin >> t2;

cout << "--->";
  cin >> scalar;

cout<<" Time 1 + Time 2 ="<< t1+t2 <<endl;
cout<<" Time 1 - time 2 ="<< t1-t2 <<endl;
cout<<" time 1 / your scalar ="<< t1/scalar <<endl;
cout<<" Time 1 * your scalar ="<< t1*scalar<<endl;

 if (t1 == t2){
     cout<< "Time 1 and Time 2 are equal"<<endl;
    }

 else {
     cout<< "Time 1 and 2 are not equal" <<endl;
    }

 if (t1 < t2){
     cout << "Time 1, " << t1 << "Is less than Time 2, " << t2 << endl;
    }
 else{
     cout << "Time 2, " << t2 << "Is less than Time 1, " << t1 << endl;  
     }
 if (t1 <= t2){
     cout << "Time 1 <= Time 2 " <<endl;
};

return (0);
}
