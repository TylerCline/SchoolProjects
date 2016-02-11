#include<string>
#include<iostream>
using namespace std;

void reversing(string &r, int &st,int &en);

int main(){
    string s;
    int start, end;
    cout<<"Enter a string:";
    getline(cin,s);
    cout<<"Now enter two numbers that are within the bounds of the string.";
    cin>>start>>end;
    cout<<"This is how your words look now:\n";
    reversing(s,start,end);
    cout<<s<<endl;
return 0;
}


void reversing(string& r, int& st, int& en)
{
    
 if(st >= en)
    return;
 else if(st < en)
  {     char tmp;
	//r[en]=r[st];
        tmp = r[st];
	r[st] = r[en];
        r[en] = tmp;
	st++;
	en--;
	reversing(r, st, en);
  }
}
