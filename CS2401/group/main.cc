#include<iostream>
#include<stdlib.h>
#include<fstream>
#include<cstdlib>
#include"roads.h"
#include"trucks.h"
#include<queue>
using namespace std;

bool query(double p);

int main(int argc, char* argv[])
{
  int snow_factor = atoi(argv[2]);
  int sim = atoi(argv[1])*60;
    cout<<"sim time: "<<sim<<endl;
    cout<<"Snow Factor: "<<snow_factor<<endl;

  int simtime = sim;
  double probability=.1;
  priority_queue<roads>r;
  trucks truck[6];
  int randomindex;
  int size = 81;
  roads road[size];
  double clear_stats=0, travel_stats=0, idle_stats, total_miles=0;

ifstream ins;
 roads tmp;
  ins.open("roads.dat");
    if(ins.fail())
           {
            cout<<"no file input"<<endl;
              return 1;
           }
    else{

        while(ins >> tmp)
        {
            for(int i=0; i <= size; i++)
                road[i].input(ins);

        }
    }
  ins.close();
cout<<"Loading data..."<<endl;
cout<<"                data loaded"<<endl;
//**********************************
//Simulation
//**********************************
for(int time = 0; time < simtime; time++)
    {
     if(query(probability))
      { randomindex = rand()%size;
        r.push(road[randomindex]);
      }
       if(randomindex != size-1)
          {road[randomindex] = road[size-1];
            size--;}
     for(int i = 0; i < 6; i++)
     {
      if(!r.empty())
      {
        if(truck[i].is_idle())
      {
          truck[i].travel_miles(r.top());
          truck[i].travel_time();
          travel_stats+=truck[i].get_travel_time();

      }
      else if(truck[i].done_traveling())
      {
         truck[i].clear_rate(snow_factor);
         truck[i].clear_time(r.top());
         total_miles += r.top().get_miles();
         r.pop();
         clear_stats += truck[i].get_clear_rate();

      }
      else if(truck[i].done_plowing())
      {
        truck[i].increment_idle_time();

      }
      }
     }
    }
idle_stats = 0;

for(int i=0; i<=6; i++)
{
 idle_stats += truck[i].get_idle_time();
}

int ro=0;
ofstream out;
out.open("logfile.dat");
if(!out.fail())
{
 out<<"Total Time Idle: "<<idle_stats<<endl;
 out<<"Totlal Time Traveling: "<<travel_stats<<endl;
 out<<"Total Miles Plowed: "<<total_miles<<endl;
 out<<endl<<"Roads that did not get plowed"<<endl;
 while(!r.empty())
 {ro++;
  r.top().output(out);
  r.pop();
 }
 out<<"total roads left: "<<ro<<endl;
}
cout<<"Saving Data......"<<endl<<endl;
cout<<"                    data saved"<<endl;
out.close();



return 0;
}


bool query(double p)
{
    return (rand() < p*RAND_MAX);
}
