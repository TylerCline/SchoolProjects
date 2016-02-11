#include <iostream>
#include "numbers.h"

using namespace std;

int main(){

 numbers n1, n2;
 

 for(int i=2;i<=14;i+=2){
 n1.insert(i);
 }
 n1.display();

 n2=n1;

 n2.remove_last();
 n2.remove_last();
 n2.remove_last();
 n2.remove_last();

 for(int j=5; j<=15; j+=5){
 n2.insert(j);
 }
 n1.display();

unsigned long item = 0;
try{
      while (true) 
      { numbers n3;
        for(int i=0; i < 100; i++)
          { n3.insert(item);
            ++item;
          }
      }
   }
catch (bad_alloc){
                  cout<<"Memory failure after inserting "<<item<<endl;
}

return(0);
}
