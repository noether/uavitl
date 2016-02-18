#include "gnc.hh"

GNC::GNC():
    _sim(NULL)
{
}

GNC::GNC(int id, Sim *sim):
    _id(id),
    _sim(sim)
{
}

GNC::~GNC()
{
}
