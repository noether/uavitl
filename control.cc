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
    _gui(g)
{
    float kt = _nav->get_kt();
    float km = _nav->get_km();
    float  l = _nav->get_l();
    _w_to_Tlmn << -kt,   -kt,   -kt,   -kt,
                    0, -l*kt,     0, -l*kt,
                -l*kt,     0, -l*kt,     0,
                  -km,    km,   -km,    km;
    _Tlmn_to_w = _w_to_Tlmn.inverse();
}

Control::~Control()
{
}

void Control::control_att()
{
    // Navigation data
    Eigen::Matrix3f J = _nav->get_J();
    float Jxx = J(0, 0);
    float Jyy = J(1, 1);
    float Jzz = J(2, 2);
    float pqr[3];
    _nav->get_pqr(pqr);

    // Control errors
    float ephi = _nav->get_roll() - _gui->get_roll_d();
    float ethe = _nav->get_pitch() - _gui->get_pitch_d();
    float epsi = _nav->get_yaw() - _gui->get_yaw_d();

    // Desired moments
    _l_d = -Jxx*(ephi + _kp*pqr[0]) - (Jyy-Jzz)*pqr[1]*pqr[2];
    _m_d = -Jyy*(ethe + _kq*pqr[1]) - (Jzz-Jxx)*pqr[2]*pqr[0];
    _n_d = -Jzz*(epsi + _kr*pqr[2]);
}

void Control::control_motors()
{
    Eigen::Vector4f Tlmn_d;
    Tlmn_d << _gui->get_T_d(), _l_d, _m_d, _n_d;
    Eigen::Vector4f w = _Tlmn_to_w * Tlmn_d;
    // XPlane needs of a normalization factor, inputs between 0 and 1
    // It depends on your gains !!
    Eigen::Array4f u = w.array().sqrt() / 500;
    _sim->set_tc(u(0), u(1), u(2), u(3),
            0.0, 0.0, 0.0, 0.0);
}

void Control::update()
{
}
