#include <iostream>
#include <string>
#include <math.h>

#include "sim.hh"
#include "./comm/udp_client_server.hh"
#include "./XPlane/XPdata.hh"
#include "./environment/gravity.hh"

Sim::Sim():
    _ip("0.0.0.0"),
    _simulator(NONE),
    _server(udp_server("0.0.0.0", -1)),
    _client(udp_client("0.0.0.0", -1)),
    _aoa(-999), _aos(-999),
    _atm_pressure(-999),
    _roll(-999), _pitch(-999), _yaw(-999),
    _gear(-999), _brakew(-999), _brakel(-999), _braker(-999),
    _latitude(-999), _longitude(-999), _altitude_msl(-999),
    _gx(-999), _gy(-999), _gz(-999),
    _ax(-999), _ay(-999), _az(-999),
    _wx(-999), _wy(-999), _wz(-999),
    _vkias(-999),
    _t1c(-999), _t2c(-999), _t3c(-999), _t4c(-999),
    _t5c(-999), _t6c(-999), _t7c(-999), _t8c(-999),
    _t1a(-999), _t2a(-999), _t3a(-999), _t4a(-999),
    _t5a(-999), _t6a(-999), _t7a(-999), _t8a(-999),
    _x(-999), _y(-999), _z(-999),
    _ve(-999), _vn(-999), _vu(-999),
    _elevc(-999), _ailc(-999), _rudc(-999)
{
}

Sim::Sim(std::string ip, int udp_port_in,
        int udp_port_out, Simulator simulator):
    _ip(ip),
    _simulator(simulator),
    _server(udp_server(_ip.c_str(), udp_port_out)),
    _client(udp_client(_ip.c_str(), udp_port_in)),
    _aoa(-999), _aos(-999),
    _atm_pressure(-999),
    _roll(-999), _pitch(-999), _yaw(-999),
    _gear(-999), _brakew(-999), _brakel(-999), _braker(-999),
    _latitude(-999), _longitude(-999), _altitude_msl(-999),
    _gx(-999), _gy(-999), _gz(-999),
    _ax(-999), _ay(-999), _az(-999),
    _wx(-999), _wy(-999), _wz(-999),
    _vkias(-999),
    _t1c(-999), _t2c(-999), _t3c(-999), _t4c(-999),
    _t5c(-999), _t6c(-999), _t7c(-999), _t8c(-999),
    _t1a(-999), _t2a(-999), _t3a(-999), _t4a(-999),
    _t5a(-999), _t6a(-999), _t7a(-999), _t8a(-999),
    _x(-999), _y(-999), _z(-999),
    _ve(-999), _vn(-999), _vu(-999),
    _elevc(-999), _ailc(-999), _rudc(-999)
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
    std::cout << "Read bytes: " << readBytes << std::endl;
    if (readBytes < 0)
        return readBytes;
    _datagram.resize(readBytes);

    return readBytes;
}

void Sim::readFromSim(){
    if(_simulator == XPLANE){
        XPdataVector v;

        if(_readDatagram() > 0)
        {
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
}

Simulator Sim::get_simulator()
{
    return _simulator;
}

void Sim::clearvout()
{
    vout.clear();
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

float Sim::get_ax()
{
    return _ax;
}

float Sim::get_ay()
{
    return _ay;
}

float Sim::get_az()
{
    return _az;
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

float Sim::get_ve()
{
    return _ve;
}

float Sim::get_vn()
{
    return _vn;
}

float Sim::get_vu()
{
    return _vu;
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

void Sim::set_tc(float t1, float t2, float t3, float t4,
        float t5, float t6, float t7, float t8)
{
    if(_simulator == XPLANE)
    {
        vout.push_back(std::tr1::shared_ptr<XPdata>
                (new XPthrottelc(t1, t2, t3, t4, t5, t6, t7, t8)));
    }
}

void Sim::sendToSim()
{
    if(_simulator == XPLANE)
    {
        std::vector<char> _dtg;
        XPdata::prologue_to_dtg(_dtg);
        for (XPdataVector::const_iterator i(vout.begin()),
                i_end(vout.end()); i != i_end; ++i){
            (*i)->to_dtg(_dtg);
        }

        _client.send(&*_dtg.begin(), _dtg.size());
        clearvout();
    }
}

void Sim::visit(XPaerangles * xp)
{
    _aoa = xp->get_aoa()*M_PI/180;
    _aos = xp->get_aos()*M_PI/180;
}

void Sim::visit(XPatmosphere * xp)
{
    _atm_pressure = xp->get_AMpressure();
}

void Sim::visit(XPattitude * xp)
{
    _roll = xp->get_roll()*M_PI/180;
    _pitch = xp->get_pitch()*M_PI/180;
    _yaw = xp->get_yaw()*M_PI/180;
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
    _latitude = xp->get_latitude()*M_PI/180;
    _longitude = xp->get_longitude()*M_PI/180;
    _altitude_msl = xp->get_altitudeFmsl()*0.3048; // Feet to meters
}

void Sim::visit(XPloads * xp)
{
    // WGS84 gravity model
    float g = _gravity.g(_latitude, _altitude_msl);

    // NED frame of coordinates
    _gx = xp->get_gAxial();
    _gy = xp->get_gSide();
    _gz = xp->get_gNormal();

    _ax = _gx * g;
    _ay = _gy * g;
    _az = _gz * g;
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
    // In XPlane, X points at the EAST, Y at UP and Z at SOUTH
    _x =  -xp->get_z();
    _y =   xp->get_x();
    _z =  -xp->get_y();
    _ve =  xp->get_vx();
    _vn = -xp->get_vz();
    _vu =  xp->get_vy();
}

void Sim::visit(XPyoke * xp)
{
    _ailc = xp->get_ail();
    _elevc = xp->get_elev();
    _rudc = xp->get_rud();
}
