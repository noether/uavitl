#ifndef FLYING_MACHINE_HH
#define FLYING_MACHINE_HH 1

#include "Eigen/Core"

#include "sim.hh"
#include "gnc.hh"

class Flyingmachine
{
    protected:
        Sim _sim;
        double _lat, _lon, _alt_msl;
        double _lat_g, _lon_g, _alt_msl_g;
        double _pitch, _roll, _yaw;

        Eigen::Vector3d _pos_eci;
        Eigen::Vector3d _pos_ecef;
        Eigen::Vector3d _pos_eci_g;
        Eigen::Vector3d _pos_ecef_g;
        Eigen::Vector3d _pos_enu;
        Eigen::Vector3d _vel_enu;
        Eigen::Vector3d _vel_body;
        Eigen::Vector3d _pqr_body;
        Eigen::Vector3d _acc_body;
        Eigen::Vector3d _mag_body;

        GNC _gnc;

    public:
        void set_gnc(GNC);

};

#endif
