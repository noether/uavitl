#include <iostream>
#include <string>

#include "sim.hh"
#include "./comm/udp_client_server.hh"
#include "./XPlane/XPdata.hh"

Sim::Sim(std::string ip, int udp_port_in,
        int udp_port_out, Simulator simulator):
    _ip(ip),
    _simulator(simulator),
    _server(udp_server(_ip.c_str(), udp_port_out)),
    _client(udp_client(_ip.c_str(), udp_port_in))
{
}

Sim::~Sim()
{
}

void Sim::connect(){
    _server.connect();
    _client.connect();
}

int Sim::_readDatagram(){
    int readBytes = 0;

    _datagram.resize(1000, 0);
    readBytes = _server.recv(&*_datagram.begin(), _datagram.size(), 0);
    if (readBytes < 0)
        return readBytes;
    _datagram.resize(readBytes);

    return readBytes;
}

void Sim::readFromSim(){
    if(_simulator == XPLANE){
        XPdataVector v;

        _readDatagram();
        int isData = 1;
        const char *data= "DATA";

        std::vector<char>::iterator i(_datagram.begin());
        std::vector<char>::iterator ii(_datagram.end());

        for(int iii = 0; iii < 4; ++iii)
            if (*(i+iii) != data[iii])
                isData = 0;

        if(isData){
            std::tr1::shared_ptr<XPdata> _xpd;
            i+=5;

            while(i != (ii)){
                _xpd.reset(XPdata::create(i));
                if(_xpd)
                    v.push_back(_xpd);
            }
        }

        for(auto v_i(v.begin()); v_i != v.end(); ++v_i)
            (*v_i)->accept(this);
    }
}

Simulator Sim::get_simulator()
{
    return _simulator;
}

float Sim::get_aoa()
{
    return _aoa;
}

float Sim::get_aos()
{
    return _aos;
}

float Sim::get_atm_pressure()
{
    return _atm_pressure;
}

float Sim::get_roll()
{
    return _roll;
}

float Sim::get_pitch()
{
    return _pitch;
}

float Sim::get_yaw()
{
    return _yaw;
}

float Sim::get_gear()
{
    return _gear;
}

float Sim::get_brakew()
{
    return _brakew;
}

float Sim::get_brakel()
{
    return _brakel;
}

float Sim::get_braker()
{
    return _braker;
}

float Sim::get_latitude()
{
    return _latitude;
}

float Sim::get_longitude()
{
    return _longitude;
}

float Sim::get_altitude_msl()
{
    return _altitude_msl;
}

float Sim::get_gx()
{
    return _gx;
}

float Sim::get_gy()
{
    return _gy;
}

float Sim::get_gz()
{
    return _gz;
}

float Sim::get_wx()
{
    return _wx;
}

float Sim::get_wy()
{
    return _wy;
}

float Sim::get_wz()
{
    return _wz;
}

float Sim::get_vkias()
{
    return _vkias;
}

float Sim::get_t1c()
{
    return _t1c;
}

float Sim::get_t2c()
{
    return _t2c;
}

float Sim::get_t3c()
{
    return _t3c;
}

float Sim::get_t4c()
{
    return _t4c;
}

float Sim::get_t5c()
{
    return _t5c;
}

float Sim::get_t6c()
{
    return _t6c;
}

float Sim::get_t7c()
{
    return _t7c;
}

float Sim::get_t8c()
{
    return _t8c;
}

float Sim::get_t1a()
{
    return _t1a;
}

float Sim::get_t2a()
{
    return _t2a;
}

float Sim::get_t3a()
{
    return _t3a;
}

float Sim::get_t4a()
{
    return _t4a;
}

float Sim::get_t5a()
{
    return _t5a;
}

float Sim::get_t6a()
{
    return _t6a;
}

float Sim::get_t7a()
{
    return _t7a;
}

float Sim::get_t8a()
{
    return _t8a;
}

float Sim::get_x()
{
    return _x;
}

float Sim::get_y()
{
    return _y;
}

float Sim::get_z()
{
    return _z;
}

float Sim::get_vx()
{
    return _vx;
}

float Sim::get_vy()
{
    return _vy;
}

float Sim::get_vz()
{
    return _vz;
}

float Sim::get_elevc()
{
    return _elevc;
}

float Sim::get_ailc()
{
    return _ailc;
}

float Sim::get_rudc()
{
    return _rudc;
}

void Sim::visit(XPaerangles * xp)
{
    _aoa = xp->get_aoa();
    _aos = xp->get_aos();
}

void Sim::visit(XPatmosphere * xp)
{
    _atm_pressure = xp->get_AMpressure();
}

void Sim::visit(XPattitude * xp)
{
    _roll = xp->get_roll();
    _pitch = xp->get_pitch();
    _yaw = xp->get_yaw();
}

void Sim::visit(XPgearbrakes * xp)
{
    _brakew = xp->get_bw();
    _braker = xp->get_br();
    _brakel = xp->get_bl();
    _gear = xp->get_gear();
}

void Sim::visit(XPgps * xp)
{
    _latitude = xp->get_latitude();
    _longitude = xp->get_longitude();
    _altitude_msl = xp->get_altitudeFmsl();
}

void Sim::visit(XPloads * xp)
{
    _gx = xp->get_gAxial();
    _gy = xp->get_gSide();
    _gz = xp->get_gNormal();
}

void Sim::visit(XPpqr * xp)
{
    _wx = xp->get_p();
    _wy = xp->get_q();
    _wz = xp->get_r();
}

void Sim::visit(XPspeeds * xp)
{
    _vkias = xp->get_vindKias();
}

void Sim::visit(XPthrottela * xp)
{
    _t1a = xp->get_t1a();
    _t2a = xp->get_t2a();
    _t3a = xp->get_t3a();
    _t4a = xp->get_t4a();
    _t5a = xp->get_t5a();
    _t6a = xp->get_t6a();
    _t7a = xp->get_t7a();
    _t8a = xp->get_t8a();
}

void Sim::visit(XPthrottelc * xp)
{
    _t1c = xp->get_t1c();
    _t2c = xp->get_t2c();
    _t3c = xp->get_t3c();
    _t4c = xp->get_t4c();
    _t5c = xp->get_t5c();
    _t6c = xp->get_t6c();
    _t7c = xp->get_t7c();
    _t8c = xp->get_t8c();
}

void Sim::visit(XPxyz * xp)
{
    _x = xp->get_x();
    _y = xp->get_y();
    _z = xp->get_z();
    _vx = xp->get_vx();
    _vy = xp->get_vy();
    _vz = xp->get_vz();
}

void Sim::visit(XPyoke * xp)
{
    _ailc = xp->get_ail();
    _elevc = xp->get_elev();
    _rudc = xp->get_rud();
}
