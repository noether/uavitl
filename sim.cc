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
    readBytes = _server.recv(&*_datagram.begin(), _datagram.size());
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
    _ax = xp->get_gAxial();
    _ay = xp->get_gSide();
    _az = xp->get_gNormal();
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
