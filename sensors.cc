#include "sensors.hh"
#include "./environment/gravity.hh"
#include "sim.hh"

Sensors::Sensors():
    _sim(NULL)
{
}

Sensors::Sensors(Sim *s):
    _sim(s)
{
}

Sensors::~Sensors()
{
}

void Sensors::read_all()
{
    read_accelerometers();
    read_gyroscopes();
    read_magnetometers();
    read_gps_coord();
    read_gps_venu();
    read_pressures();
    read_aoa();
    read_aos();
}

void Sensors::read_accelerometers()
{
    _ax = _sim->get_ax();
    _ay = _sim->get_ay();
    _az = _sim->get_az();
}

void Sensors::read_gyroscopes()
{
    _wx = _sim->get_wx();
    _wy = _sim->get_wy();
    _wz = _sim->get_wz();
}

void Sensors::read_magnetometers()
{

}

void Sensors::read_gps_coord()
{
    _lat = _sim->get_latitude();
    _lon = _sim->get_longitude();
    _amsl = _sim->get_altitude_msl();
}

void Sensors::read_gps_venu()
{

}

void Sensors::read_pressures()
{
    _spres = _sim->get_atm_pressure();
}

void Sensors::read_aoa()
{
    _aoa = _sim->get_aoa();
}

void Sensors::read_aos()
{
    _aos = _sim->get_aos();
}

void Sensors::get_accelerometers(float *s)
{
    s[0] = _ax;
    s[1] = _ay;
    s[2] = _az;
}

void Sensors::get_gyroscopes(float *s)
{
    s[0] = _wx;
    s[1] = _wy;
    s[2] = _wz;
}

void Sensors::get_magnetometers(float *s)
{
    s[0] = _mx;
    s[1] = _my;
    s[2] = _mz;
}

void Sensors::get_gps_coord(float *s)
{
    s[0] = _lat;
    s[1] = _lon;
    s[2] = _amsl;
}

void Sensors::get_gps_venu(float *s)
{
    s[0] = _ve;
    s[1] = _vn;
    s[2] = _vu;
}

void Sensors::get_pressures(float *s)
{
    s[0] = _spres;
    s[1] = _dpres;
}

void Sensors::get_aoa(float *s)
{
    s[0] = _aoa;
}

void Sensors::get_aos(float *s)
{
    s[0] = _aos;
}
