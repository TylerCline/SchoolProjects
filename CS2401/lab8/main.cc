#include<stack>
#include<iostream>
#include<cctype>
using namespace std;



//double evaluate(double num1, double num2, char op);

int evaluate(int num1, int num2, char op);

bool isop(char op);


int main(){

stack<char>ops;
stack<int>nums;
int n1, n2, n3;
char tmp, ans;


while( ans != 'n')
{
 bool error = false;
 cin.sync();
 while(!nums.empty())
         {nums.pop();}
 cout<<"Type in the expression"<<endl<<endl;
 tmp = cin.get();
 while(tmp != '\n')
     { if(isdigit(tmp))
          { 
            cin.putback(tmp);
            cin >> n1;
	    nums.push(n1);
          }
       else if(isop(tmp))
          {
            if(nums.size()<2)
              { cout<<"not enough elements"<<endl<<endl;
		error = true;
	      }
            else
              {
               n2 = nums.top();
               nums.pop();
               n1 = nums.top();
               nums.pop();
	       n3 = evaluate(n1, n2, tmp);
               nums.push(n3);
              }
          }
 tmp = cin.get();   
     }
if (error == false)
{ if(nums.size()>1)
   {cout<<"Error: too many elements"<<endl<<endl;}
  else if(nums.size()==1)
   {cout<<nums.top()<<endl<<endl;}
 
  cout<<"enter 'n' to stop"<<endl<<endl;
  cin>>ans;
 }
}

return (0);
}




bool isop(char op){
        return op =='+' || op == '-' || op == '*' || op == '/';
}

int evaluate(int num1, int num2, char op){
    if(op == '+') return num1 + num2;
    if(op == '-') return num1-num2;
    if(op == '*') return num1*num2;
    if(op == '/') return num1/num2;
    else return 0;
}

/*double evaluate(double num1, double num2, char op){
    if(op == '+') return num1 + num2;
    if(op == '-') return num1-num2;
    if(op == '*') return num1*num2;
    if(op == '/') return num1/num2;
    else return 0;
}*/
