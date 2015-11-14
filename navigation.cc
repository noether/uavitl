#include "navigation.hh"

Navigation::Navigation():
    _aoa(-999), _aos(-999),
    _atm_pressure(-999),
    _roll(-999), _pitch(-999), _yaw(-999),
    _latitude(-999), _longitude(-999), _altitude_msl(-999),
    _ax(-999), _ay(-999), _az(-999),
    _wx(-999), _wy(-999), _wz(-999),
    _vkias(-999),
    _x(-999), _y(-999), _z(-999),
    _vx(-999), _vy(-999), _vz(-999),
    _sim(NULL), _sen(NULL)
{
}

Navigation::Navigation(Sim *si, Sensors *se):
    _aoa(-999), _aos(-999),
    _atm_pressure(-999),
    _roll(-999), _pitch(-999), _yaw(-999),
    _latitude(-999), _longitude(-999), _altitude_msl(-999),
    _ax(-999), _ay(-999), _az(-999),
    _wx(-999), _wy(-999), _wz(-999),
    _vkias(-999),
    _x(-999), _y(-999), _z(-999),
    _vx(-999), _vy(-999), _vz(-999),
    _sim(si), _sen(se)
{
}

Navigation::~Navigation()
{
}

void Navigation::update()
{
    _roll = _sim->get_roll();
    _pitch = _sim->get_pitch();
    _yaw = _sim->get_yaw();

    std::cout << _roll << std::endl;
}
