#include "sim.hh"
#include "flyingmachine.hh"
#include "gnc.hh"

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
    _sim->readFromSim();
    return 0;
}
