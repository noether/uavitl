#include "sim.hh"
#include "flyingmachine.hh"
#include "gnc.hh"
#include "./XPlane/XPdata.hh"

#include <iostream>

Flyingmachine::Flyingmachine(Sim *sim, GNC *gnc):
    _sim(sim),
    _gnc(gnc)
{
    _sim->connect();
}

Flyingmachine::~Flyingmachine()
{
}

int Flyingmachine::update(int t)
{
    if (_sim->get_simulator() == XPLANE)
        _sim->readFromSim();

    return 0;
}
