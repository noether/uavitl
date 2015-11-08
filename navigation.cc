#include "navigation.hh"

Navigation::Navigation():
    _raw_aoa(-999), _raw_aos(-999),
    _raw_atm_pressure(-999),
    _raw_roll(-999), _raw_pitch(-999), _raw_yaw(-999),
    _raw_latitude(-999), _raw_longitude(-999), _raw_altitude_msl(-999),
    _raw_ax(-999), _raw_ay(-999), _raw_az(-999),
    _raw_wx(-999), _raw_wy(-999), _raw_wz(-999),
    _raw_vkias(-999),
    _raw_x(-999), _raw_y(-999), _raw_z(-999),
    _raw_vx(-999), _raw_vy(-999), _raw_vz(-999)
{
}

Navigation::~Navigation()
{
}
