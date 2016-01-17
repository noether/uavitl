#include "sensors.hh"
#include "./environment/gravity.hh"
#include "sim.hh"

Sensors::Sensors():
    _sim(NULL)
{
}

Sensors::Sensors(Sim *sim):
    _sim(sim)
{
}

Sensors::~Sensors()
{
}
