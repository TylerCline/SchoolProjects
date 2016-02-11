#include<iostream>
#include"roads.h"
#ifndef TRUCKS_H
#define TRUCKS_H

class trucks{
public:
	trucks();
	void clear_rate(int snow_factor);

	void clear_time(roads c);

	double get_clear_rate()
		{return clear_time1;}

	void increment_idle_time()
        {
            idle++;
        }

	int get_idle_time()
		{return idle;}

    void travel_miles(roads q);

	void travel_time();

	int get_travel_mileage()
		{return travel_milage;}

	int get_travel_time()
		{return travel_time1;}

    double get_x()
        {return x;}

	double get_y()
		{return y;}

	bool is_traveling();
	bool is_plowing();
	bool is_idle();
        bool done_traveling();
    	bool done_plowing();

private:
	double clear, miles, travel_milage;
	double travel_time1, clear_time1, idle, plow_time_left, travel_time_left;
    	double x, y;

};
#endif
