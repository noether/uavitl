#ifndef NAVIGATION_HH
#define NAVIGATION_HH 1

#include "sim.hh"
#include "sensors.hh"

class Navigation
{
    private:
        float _aoa, _aos;
        float _atm_pressure;
        float _roll, _pitch, _yaw;
        float _gear, _brakew, _brakel, _braker;
        float _latitude, _longitude, _altitude_msl;
        float _ax, _ay, _az;
        float _wx, _wy, _wz;
        float _vkias;
        float _t1c, _t2c, _t3c, _t4c, _t5c, _t6c, _t7c, _t8c;
        float _x, _y, _z;
        float _vx, _vy, _vz;
        float _elevc, _ailc, _rudc;

        // Mechanics
        Eigen::Matrix3f _J; // Inertia matrix [Kg/m^2]
        float _l; // Radius of the quad [m]
        float _m; // Mass of the quad [Kg]
        float _kt; // Propeller thrust [N s^2]
        float _km; // Propeller thrust [N m s^2]

        Sim * _sim;
        Sensors * _sen;

    public:
        Navigation();
        Navigation(Sim *, Sensors *);
        ~Navigation();

        void get_body_accelerations(float *);
        void get_pqr(float *);
        void get_xyz(float *);
        void get_v_ned(float *);
        float get_roll();
        float get_pitch();
        float get_yaw();
        float get_altitude_msl();
        Eigen::Matrix3f get_J();
        float get_l();
        float get_m();
        float get_kt();
        float get_km();

        void update();
};

#endif
