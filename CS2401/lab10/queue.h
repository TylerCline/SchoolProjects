#include<string>
#include<iostream>

class chore{
  public:
         chore(){priority=0;}
         bool operator < (const chore& other)const
                         {return priority<other.priority;}
         void input();
         void output()const;

  private:
          std::string description;
          int priority;
};
