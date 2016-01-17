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
        Sensors *_sen;
        GNC *_gnc;

    public:
        Flyingmachine();
        Flyingmachine(Sim*, Sensors*, GNC*);
        ~Flyingmachine();

        void update(long t);
};

#endif
