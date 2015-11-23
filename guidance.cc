#include "guidance.hh"
#include "Eigen/Core"
#include "./math/math_util.hh"

Guidance::Guidance():
    _nav(NULL)
{
}

Guidance::Guidance(Navigation *n):
    _nav(n)
{
     _m = 1;
     _aE = 0;
     _aN = 0;
     _aU = 0;
}

Guidance::~Guidance()
{
}

float Guidance::get_e_amsl()
{
    return _e_amsl;
}

float Guidance::get_e_psi()
{
    return _e_psi;
}

float Guidance::get_e_phi()
{
    return _e_phi;
}

float Guidance::get_e_the()
{
    return _e_the;
}

void Guidance::update()
{
    float psi = _nav->get_yaw();
    float body_acc[3];
    _nav->get_body_accelerations(body_acc);

    float tps = tanf(psi);
    float cps = cosf(psi);

    float g_altitude_msl = 3000;
    float g_psi = 0;
    float g_phi = (-_aN + _aE*tps) * cps / body_acc[2];
    float g_the = (_aE + _aN*tps) * cps / body_acc[2];

    _e_amsl = _nav->get_altitude_msl() - g_altitude_msl;
    _e_psi  = _nav->get_yaw() - g_psi;
    _e_phi  = _nav->get_roll() - g_phi;
    _e_the  = _nav->get_pitch() - g_the;
}
