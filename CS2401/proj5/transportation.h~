#include<iostream>

class transportation{
    public:
           virtual void input(std::istream& in)=0;
           virtual void output(std::ostream& out)=0;
    private:

};

class stratofortress:public transportation{
    public:
           stratofortress();
           void input(std::istream& in);
           void output(std::ostream& out);
    private:
           std::string propeller_engine_type, armaments, capable_elevation;
           double ammunition_mm, crew_capacity;


};

class cruise_ship:public transportation{
    public:
           cruise_ship();
           void input(std::istream& in);
           void output(std::ostream& out);

    private:
            std::string activities, name;
            double approx_bouyancy;
            int approx_knots;
};

class semi_truck:public transportation{
    public:
           semi_truck();
           void input(std::istream& in);
           void output(std::ostream& out);

    private:
            std::string make, model, company;
            double trailer_size, num_of_gears;

};

class kayak:public transportation{
    public:
           kayak();
           void input(std::istream& in);
           void output(std::ostream& out);
    private:
            std::string kayak_type;
            double thickness, weight_limit, length;

};

class zeppelin:public transportation{
    public:
           zeppelin();
           void input(std::istream& in);
           void output(std::ostream& out);
    private:
           std::string gas_type, bag_material_type;
           double num_of_bags, cabin_occupancy;
};

class destroyer:public transportation{
    public:
           destroyer();
           void input(std::istream& in);
           void output(std::ostream& out);
    private:
            std::string weapons, type, propulsion;
            double bouyancy;
            int num_of_barracks;

};
