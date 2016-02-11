#include<iostream>
#include<string>
#include"trucks.h"
#include"roads.h"
using namespace std;

trucks::trucks(){

x=0;
y=0;
clear=0;
clear_time1=0;
travel_milage=0;
travel_time1=0;
idle=0;
miles=0;
travel_time_left=0;
plow_time_left=0;
}

void trucks::clear_rate(int snow_factor)
{
    clear = 6*snow_factor;
}

void trucks::clear_time(roads c)
{
    clear_time1 = plow_time_left = clear*c.get_miles();
    if(plow_time_left > 0)
    {
        plow_time_left--;
    }
 x = c.get_x_coordinate();
 y = c.get_y_coordinate();

}


void trucks::travel_miles(roads q)
{
     int x1, y1;
	 x1=q.get_x_coordinate()-x;
	 y1=q.get_y_coordinate()-y;
     travel_milage=x1+y1*y1;
}

void trucks::travel_time()
{
   travel_time1 = travel_time_left = travel_milage*(.16);
   if(travel_time_left > 0)
   {
       travel_time_left--;
   }
}


bool trucks::is_traveling(){
	if(travel_time_left > 0)
        return true;
    else
        return false;
}

bool trucks::done_traveling()
{
    if(travel_time_left == 0)
        return true;
    else
        return false;
}

bool trucks::done_plowing()
{
    if(plow_time_left == 0)
        return true;
    else
        return false;
}

bool trucks::is_idle()
{
    if(travel_time_left ==0 && plow_time_left == 0)
        return true;
    else
        return false;
}

bool trucks::is_plowing()
{
    if(plow_time_left > 0)
        return true;
    else
        return false;
}




