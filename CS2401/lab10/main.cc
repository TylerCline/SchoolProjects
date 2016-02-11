#include<iostream>
#include<queue>
#include<string>
#include"queue.h"
using namespace std;

int main()
{
priority_queue<chore> C;
chore tmp;
int count=0, i=0;

while(count != 5)
{
 tmp.input();
 C.push(tmp);
 count++;
}

while(i<5)
{
 C.top().output();
 C.pop();
 i++;
}
return 0;
}
