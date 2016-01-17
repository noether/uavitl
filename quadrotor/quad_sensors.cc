#include "quad_sensors.hh"
#include "../sim.hh"

Quad_Sensors::Quad_Sensors():
    Sensors(NULL)
{
}

Quad_Sensors::Quad_Sensors(Sim *s):
    Sensors(s)
{
}

Quad_Sensors::~Quad_Sensors()
{
}

void Quad_Sensors::update(long t)
{
    t++;
    read_accelerometers();
    read_gyroscopes();
    read_magnetometers();
    read_gps_coord();
    read_gps_venu();
    read_pressures();
}

void Quad_Sensors::read_accelerometers()
{
    _ax = _sim->get_ax();
    _ay = _sim->get_ay();
    _az = _sim->get_az();
}

void Quad_Sensors::read_gyroscopes()
{
    _wx = _sim->get_wx();
    _wy = _sim->get_wy();
    _wz = _sim->get_wz();
}

void Quad_Sensors::read_magnetometers()
{
    _mx = 0;
    _my = 0;
    _mz = 0;
}

void Quad_Sensors::read_gps_coord()
{
    _lat = _sim->get_latitude();
    _lon = _sim->get_longitude();
    _amsl = _sim->get_altitude_msl();
}

void Quad_Sensors::read_gps_venu()
{
    _ve = _sim->get_ve();
    _vn = _sim->get_vn();
    _vu = _sim->get_vu();
}

void Quad_Sensors::read_pressures()
{
    _spres = _sim->get_atm_pressure();
}


void Quad_Sensors::get_accelerometers(float *s)
{
    s[0] = _ax;
    s[1] = _ay;
    s[2] = _az;
}

void Quad_Sensors::get_gyroscopes(float *s)
{
    s[0] = _wx;
    s[1] = _wy;
    s[2] = _wz;
}

void Quad_Sensors::get_magnetometers(float *s)
{
    s[0] = _mx;
    s[1] = _my;
    s[2] = _mz;
}

void Quad_Sensors::get_gps_coord(float *s)
{
    s[0] = _lat;
    s[1] = _lon;
    s[2] = _amsl;
}

void Quad_Sensors::get_gps_v_enu(float *s)
{
    s[0] = _ve;
    s[1] = _vn;
    s[2] = _vu;
}

void Quad_Sensors::get_pressures(float *s)
{
    s[0] = _spres;
}
