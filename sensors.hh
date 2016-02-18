#ifndef SENSORS_HH
#define SENSORS_HH 1

#include "Eigen/Core"
#include "sim.hh"
#include "./environment/gravity.hh"

class Sensors
{
    protected:
        int _id;
        Sim * _sim;

    public:
        Sensors(int, Sim *);
        Sensors();
        ~Sensors();

        virtual void update(long) =0;
};

#endif
