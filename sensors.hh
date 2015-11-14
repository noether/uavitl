#ifndef SENSORS_HH
#define SENSORS_HH 1

#include "Eigen/Core"
#include "sim.hh"
#include "./environment/gravity.hh"

class Sensors
{
    private:
        float _ax, _ay, _az;
        float _wx, _wy, _wz;
        float _mx, _my, _mz;
        float _lat, _lon, _amsl;
        float _vkias;
        float _ve, _vn, _vu;
        float _roll, _pitch, _yaw;
        float _aoa, _aos;
        float _spres, _dpres;
        Sim * _sim;

    public:
        Sensors(Sim *);
        Sensors();
        ~Sensors();

        void read_all();

        void read_accelerometers();
        void read_gyroscopes();
        void read_magnetometers();
        void read_gps_coord();
        void read_gps_venu();
        void read_pressures();
        void read_aoa();
        void read_aos();

        void get_accelerometers(float *);
        void get_gyroscopes(float *);
        void get_magnetometers(float *);
        void get_gps_coord(float *);
        void get_gps_venu(float *);
        void get_pressures(float *);
        void get_aoa(float *);
        void get_aos(float *);
};

#endif
