#ifndef QUAD_SENSORS_HH
#define QUAD_SENSORS_HH 1

#include "../sensors.hh"
#include "../sim.hh"

class Quad_Sensors: public Sensors{
    private:
        float _ax, _ay, _az;
        float _wx, _wy, _wz;
        float _mx, _my, _mz;
        float _lat, _lon, _amsl;
        float _ve, _vn, _vu;
        float _roll, _pitch, _yaw;
        float _spres;

    public:
        Quad_Sensors(int, Sim *);
        Quad_Sensors();
        ~Quad_Sensors();

        void update(long);

        void read_accelerometers();
        void read_gyroscopes();
        void read_magnetometers();
        void read_gps_coord();
        void read_gps_venu();
        void read_pressures();

        void get_accelerometers(float *);
        void get_gyroscopes(float *);
        void get_magnetometers(float *);
        void get_gps_coord(float *);
        void get_gps_v_enu(float *);
        void get_pressures(float *);
};

#endif
