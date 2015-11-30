#include "control.hh"
#include "Eigen/Core"
#include "Eigen/LU"

Control::Control():
    _sim(NULL),
    _nav(NULL),
    _gui(NULL)
{
}

Control::Control(Sim *s, Navigation *n, Guidance *g):
    _sim(s),
    _nav(n),
    _gui(g),
    _kf(1),
    _dkf(1e-1),
    _km(1e-1)
{
    Eigen::Matrix4f aux;
    aux << _kf, _kf, _kf, _kf,
           0, _dkf, 0, -_dkf,
           -_dkf, 0, _dkf, 0,
           _km, -_km, _km, -_km;
    uf_to_u = aux.inverse();
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
    float e_az = _gui->get_e_az();

    float pqr[3];
    _nav->get_pqr(pqr);

    float T = -e_az;
    float l = -1e-1*e_phi - 1e-1*pqr[0] - pqr[1]*pqr[2];
    float m = -1e-1*e_the - 1e-1*pqr[1] - pqr[0]*pqr[2];
    float n = -1e-1*e_psi - 1e-1*pqr[2] - pqr[0]*pqr[1];

    Eigen::Vector4f u_f, u;
    u_f << T, l, m, n;

    if(pqr[0] < -100)
        u_f *= 0;
    
    u = 3e-3*uf_to_u * u_f;
    std::cout << u << std::endl << std::endl;

    _sim->set_tc(u(0), u(1), u(2), u(3),
            0.0, 0.0, 0.0, 0.0);
}
