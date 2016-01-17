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
}

Guidance::~Guidance()
{
}

float Guidance::get_roll_d()
{
    return _roll_d;
}

float Guidance::get_pitch_d()
{
    return _pitch_d;
}

float Guidance::get_yaw_d()
{
    return _yaw_d;
}

float Guidance::get_alt_d()
{
    return _alt_d;
}

float Guidance::get_T_d()
{
    return _T_d;
}

void Guidance::set_xyz_ned_lya(float *xyz_d)
{
    float m;
    float psi;
    float xyz[3];
    float v_ned[3];

    m = _nav->get_mass();
    psi = _nav->get_yaw();
    _nav->get_xyz(xyz);
    _nav->get_v_ned(v_ned);

    float e_x = xyz_d[0] - xyz[0];
    float e_y = xyz_d[1] - xyz[1];
    float e_z = xyz_d[2] - xyz[2];
    _e_alt = e_z;

    az_d = (-_xi_g -_gravity_guess -_k_alt*e_z -_k_vz*v_ned[2]);
    ax_d = -_k_xy*e_x -_k_vxy*v_ned[0];
    ay_d = -_k_xy*e_y -_k_vxy*v_ned[1];

    _T_d = az_d*m;
    _roll_d = -1/az_d * (ay_d*cosf(psi) - ax_d*sinf(psi));
    _pitch_d =  1/az_d * (ax_d*cosf(psi) + ay_d*sinf(psi));
}

void step_estimator_xi(float dt)
{
    float v_ned[3];
    _nav->get_v_ned(v_ned);

    _xi_g = _xi_g + _k_xi_g_v*v_ned[2] + _k_xi_g_e_alt*_e_alt;
}

void Guidance::update(float dt)
{
    step_estimator_xi_g(dt);
}
