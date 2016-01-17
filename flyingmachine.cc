#include "sim.hh"
#include "flyingmachine.hh"
#include "gnc.hh"
#include "./XPlane/XPdata.hh"

#include <iostream>

Flyingmachine::Flyingmachine():
    _sim(NULL),
    _sen(NULL),
    _gnc(NULL)
{
}

Flyingmachine::Flyingmachine(Sim *sim, Sensors *sen, GNC *gnc):
    _sim(sim),
    _sen(sen),
    _gnc(gnc)
{
    _sim->connect();
}

Flyingmachine::~Flyingmachine()
{
}

void Flyingmachine::update(long t)
{
    _sim->readFromSim();
    if (t > 5e8){
        _sen->update(t);
        _gnc->update(t);
    }
    _sim->sendToSim();
}
