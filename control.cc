#include "control.hh"
#include "Eigen/Core"

Control::Control():
    _sim(NULL),
    _nav(NULL),
    _gui(NULL)
{
}

Control::Control(Sim *s, Navigation *n, Guidance *g):
    _sim(s),
    _nav(n),
    _gui(g)
{
}

Control::~Control()
{
}

void Control::update()
{
    float e_amsl = _gui->get_e_amsl();
    float e_psi = _gui->get_e_psi();
    float e_phi = _gui->get_e_phi();
    float e_the = _gui->get_e_the();

    std::cout << e_amsl << " " << e_psi << std::endl;

    float t1 = 0.5;
    float t2 = 0;
    float t3 = 0.5;
    float t4 = 0;

    _sim->set_tc(t1, t2, t3, t4,
            0.0, 0.0, 0.0, 0.0);
}
