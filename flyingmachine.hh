#ifndef FLYING_MACHINE_HH
#define FLYING_MACHINE_HH 1

#include "Eigen/Core"

#include "gnc.hh"
#include "sim.hh"
#include "sensors.hh"

class Flyingmachine
{
    private:
        Sim *_sim;
        GNC *_gnc;
        Sensors *_sen;

    public:
        Flyingmachine();
        Flyingmachine(Sim*, GNC*, Sensors*);
        ~Flyingmachine();

        void update(long t);
};

#endif
