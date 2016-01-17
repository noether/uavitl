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

void Navigation::get_body_accelerations(float *a)
{
    a[0] = _ax;
    a[1] = _ay;
    a[2] = _az;
}

void Navigation::get_pqr(float *w)
{
    w[0] = _wx;
    w[1] = _wy;
    w[2] = _wz;
}

void Navigation::get_xyz(float *xyz)
{
    xyz[0] = _x;
    xyz[1] = _y;
    xyz[2] = _z;
}

void get_v_ned(float *v_ned)
{
    v_ned[0] = _vx;
    v_ned[1] = _vy;
    v_ned[2] = _vz;
}

float Navigation::get_roll()
{
    return _roll;
}

float Navigation::get_pitch()
{
    return _pitch;
}

float Navigation::get_yaw()
{
    return _yaw;
}

float Navigation::get_altitude_msl()
{
    return _altitude_msl;
}

Eigen::Matrix3f Navigation::get_J()
{
    return _J;
}

float Navigation::get_m()
{
    return _m;
}

float Navigation::get_l()
{
    return _l;
}

float Navigation::get_kt()
{
    return _kt;
}

float Navigation::get_km()
{
    return _km;
}

void Navigation::update()
{
    float acc[3];
    float gyr[3];
    float gps[3];

    _sen->get_accelerometers(acc);
    _ax = acc[0];
    _ay = acc[1];
    _az = acc[2];

    _sen->get_gyroscopes(gyr);
    _wx = gyr[0];
    _wy = gyr[1];
    _wz = gyr[2];

    _sen->get_gps_coord(gps);
    _altitude_msl = gps[2];
    
    _roll = _sim->get_roll();
    _pitch = _sim->get_pitch();
    _yaw = _sim->get_yaw();
}
