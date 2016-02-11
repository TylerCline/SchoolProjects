//Header File

#include <iostream>

class MyTime
{   
  public:

    // CONVERT THESE CONSTRUCTORS INTO A SINGLE CONSTRUCTOR THAT USES 
    // DEFAULT ARGUMENTS
    MyTime();
    MyTime(int h, int m);   
   
      
    void Reset(int h, int m);    
   
    MyTime operator + (const MyTime& t2)const;
 
    MyTime operator - (const MyTime& t2)const;
 
    MyTime operator * (int num)const;

    MyTime operator / (int num)const;

    friend std::istream& operator >>(std::istream& fin, MyTime& t);
    
    friend std::ostream& operator <<(std::ostream& fout, const MyTime& t);

    bool operator == (const MyTime& t2)const;

    bool operator < (const MyTime& t2)const;

    friend bool operator <= (const MyTime& t1, const MyTime& t2);
            
    int get_hours() const{return hours;}
    int get_minutes() const{return minutes;}
   
  private:
      void simplify();
      int hours;      // hours can be > 24
      int minutes;   // 0 <= minutes <= 59
 };
