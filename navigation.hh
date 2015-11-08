#ifndef NAVIGATION_HH
#define NAVIGATION_HH 1

class Navigation
{
    private:
        float _raw_aoa, _raw_aos;
        float _raw_atm_pressure;
        float _raw_roll, _raw_pitch, _raw_yaw;
        float _gear, _brakew, _brakel, _braker;
        float _raw_latitude, _raw_longitude, _raw_altitude_msl;
        float _raw_ax, _raw_ay, _raw_az;
        float _raw_wx, _raw_wy, _raw_wz;
        float _raw_vkias;
        float _t1c, _t2c, _t3c, _t4c, _t5c, _t6c, _t7c, _t8c;
        float _raw_x, _raw_y, _raw_z;
        float _raw_vx, _raw_vy, _raw_vz;
        float _elevc, _ailc, _rudc;

    public:
        Navigation();
        ~Navigation();
};

#endif
