#include "sim.hh"
#include "flyingmachine.hh"
#include "gnc.hh"
#include "./XPlane/XPdata.hh"

#include <iostream>

Flyingmachine::Flyingmachine():
    _sim(NULL),
    _gnc(NULL),
    _sen(NULL)
{
}

Flyingmachine::Flyingmachine(Sim *sim, GNC *gnc, Sensors *sen):
    _sim(sim),
    _gnc(gnc),
    _sen(sen)
{
    _sim->connect();
}

Flyingmachine::~Flyingmachine()
{
}

void Flyingmachine::update(long t)
{
    if(_sim->get_simulator() == XPLANE)
    {
        _sim->readFromSim();
    }

    t++;
    
    _sen->read_all();
    _gnc->nav_update();
    _gnc->gui_update();
    _gnc->con_update();

    if(_sim->get_simulator() == XPLANE)
    {
        _sim->sendToSim();
        _sim->clearvout();
    }
}
