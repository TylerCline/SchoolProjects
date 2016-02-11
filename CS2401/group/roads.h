#include<iostream>
#include<string>
#ifndef ROADS_H
#define ROADS_H

class roads{
public:
	roads();

        friend std::istream& operator >>(std::istream& in, roads& c);

        void operator =(roads& c);

        bool operator <(const roads& other)const
		{return priority<other.priority;}

    void input(std::istream& in);

	double get_x_coordinate()
		{return x;}

	double get_y_coordinate()
		{return y;}

	double get_miles()const
		{return miles;}

	void output(std::ostream& outs)const;


private:
        int priority;
        double x, y, miles;
        std::string name;
};

#endif
