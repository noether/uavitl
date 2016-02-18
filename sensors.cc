#include "sensors.hh"
#include "./environment/gravity.hh"
#include "sim.hh"

Sensors::Sensors():
    _sim(NULL)
{
}

Sensors::Sensors(int id, Sim *sim):
    _id(id),
    _sim(sim)
{
}

Sensors::~Sensors()
{
}
