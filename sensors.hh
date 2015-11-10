#ifndef SENSORS_HH
#define SENSORS_HH 1

#include "Eigen/Core"

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

    public:
        Sensors();
        ~Sensors();

};

#endif
