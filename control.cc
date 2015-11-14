#include "control.hh"

Control::Control():
    _sim(NULL),
    _nav(NULL)
{
}

Control::Control(Sim *s, Navigation *n):
    _sim(s),
    _nav(n)
{
}

Control::~Control()
{
}

void Control::update()
{
    _sim->set_tc(0.1, 0.1, 0.1, 0,
            0.0, 0.0, 0.0, 0.0);
}
