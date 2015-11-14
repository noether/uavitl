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
#include "./environment/gravity.hh"

enum Simulator{
    XPLANE};

class Sim
{
    private:
        std::string _ip;
        Simulator _simulator;

        std::vector<char> _datagram;
        XPdataVector vout;
        udp_server _server;
        udp_client _client;

        int _readDatagram();

        float _aoa, _aos;
        float _atm_pressure;
        float _roll, _pitch, _yaw;
        float _gear, _brakew, _brakel, _braker;
        float _latitude, _longitude, _altitude_msl;
        float _gx, _gy, _gz;
        float _ax, _ay, _az;
        float _wx, _wy, _wz;
        float _vkias;
        float _t1c, _t2c, _t3c, _t4c, _t5c, _t6c, _t7c, _t8c;
        float _t1a, _t2a, _t3a, _t4a, _t5a, _t6a, _t7a, _t8a;
        float _x, _y, _z;
        float _vx, _vy, _vz;
        float _elevc, _ailc, _rudc;

        Gravity _gravity;

    public:
        Sim(std::string, int, int, Simulator);
        ~Sim();

        void connect();
        void readFromSim();
        void sendToSim();
        Simulator get_simulator();

        void clearvout();

        float get_aoa();
        float get_aos();
        float get_atm_pressure();
        float get_roll();
        float get_pitch();
        float get_yaw();
        float get_gear();
        float get_brakew();
        float get_brakel();
        float get_braker();
        float get_latitude();
        float get_longitude();
        float get_altitude_msl();
        float get_gx();
        float get_gy();
        float get_gz();
        float get_ax();
        float get_ay();
        float get_az();
        float get_wx();
        float get_wy();
        float get_wz();
        float get_vkias();
        float get_t1c();
        float get_t2c();
        float get_t3c();
        float get_t4c();
        float get_t5c();
        float get_t6c();
        float get_t7c();
        float get_t8c();
        float get_t1a();
        float get_t2a();
        float get_t3a();
        float get_t4a();
        float get_t5a();
        float get_t6a();
        float get_t7a();
        float get_t8a();
        float get_x();
        float get_y();
        float get_z();
        float get_vx();
        float get_vy();
        float get_vz();
        float get_elevc();
        float get_ailc();
        float get_rudc();

        void set_tc(float, float, float, float,
                float, float, float, float);

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
