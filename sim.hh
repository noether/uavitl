#ifndef SIM_HH
#define SIM_HH 1

#include <string>
#include <vector>
#include "./comm/udp_client_server.hh"
#include "./XPlane/XPdata.hh"
#include "./XPlane/XPaerangles.hh"
#include "./XPlane/XPatmosphere.hh"
#include "./XPlane/XPattitude.hh"
#include "./XPlane/XPgearbrakes.hh"
#include "./XPlane/XPgps.hh"
#include "./XPlane/XPloads.hh"
#include "./XPlane/XPpqr.hh"
#include "./XPlane/XPspeeds.hh"
#include "./XPlane/XPthrottela.hh"
#include "./XPlane/XPthrottelc.hh"
#include "./XPlane/XPxyz.hh"
#include "./XPlane/XPyoke.hh"

enum Simulator{
    XPLANE};

class Sim
{
    private:
        std::string _ip;
        Simulator _simulator;

        std::vector<char> _datagram;
        udp_server _server;
        udp_client _client;

        int _readDatagram();

        float _aoa, _aos;
        float _atm_pressure;
        float _roll, _pitch, _yaw;
        float _gear, _brakew, _brakel, _braker;
        float _latitude, _longitude, _altitude_msl;
        float _ax, _ay, _az;
        float _wx, _wy, _wz;
        float _vkias;
        float _t1c, _t2c, _t3c, _t4c, _t5c, _t6c, _t7c, _t8c;
        float _t1a, _t2a, _t3a, _t4a, _t5a, _t6a, _t7a, _t8a;
        float _x, _y, _z;
        float _vx, _vy, _vz;
        float _elevc, _ailc, _rudc;

    public:
        Sim(std::string, int, int, Simulator);
        ~Sim();

        void connect();
        void readFromSim();
        Simulator get_simulator();

        float get_aoa();
        float get_aos();

        void visit(XPaerangles *);
        void visit(XPatmosphere *);
        void visit(XPattitude *);
        void visit(XPgearbrakes *);
        void visit(XPgps *);
        void visit(XPloads *);
        void visit(XPpqr *);
        void visit(XPspeeds *);
        void visit(XPthrottela *);
        void visit(XPthrottelc *);
        void visit(XPxyz *);
        void visit(XPyoke *);
};

#endif
