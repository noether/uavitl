#ifndef QUAD_GNC_HH
#define QUAD_GNC_HH 1

#include <iostream>
#include <fstream>
#include "../gnc.hh"
#include "../sim.hh"
#include "quad_sensors.hh"

enum Controller{
    NO_CONTROLLER,
    XYZ,
    V_2D_ALT,
    A_2D_ALT,
    A_3D};

class Quad_GNC: public GNC{
    private:
        Quad_Sensors *_sen;

        // Navigation
        float _roll, _pitch, _yaw;
        float _ax, _ay, _az;
        float _vn, _ve, _vd;
        float _x, _y, _z;
        float _lat, _lon, _alt;
        float _p, _q, _r;
        Eigen::Matrix3f _J;
        float _m, _l;

        // Guidance
        float _roll_d, _pitch_d, _yaw_d;
        float _an_d, _ae_d, _ad_d;
        float _vn_d, _ve_d, _vd_d;
        float _x_d, _y_d, _z_d;
        float _alt_d;
        float _x_zero, _y_zero, _z_zero;
        Eigen::Matrix3f _ECEF_to_Nav;

        void _xyz_wrt_xyz_zero(float, float, float);

        // Control
        Controller _controller;
        Eigen::Matrix4f _w_to_Tlmn, _Tlmn_to_w;
        float _kp, _kq, _kr; // Attitude gains
        float _k_xy, _k_vxy, _k_vz, _k_alt; // Acceleration gains
        float _xi_g, _xi_CD; // Estimators
        float _k_xi_g_v, _k_xi_g_e_alt; // Gains for xi_g
        float _k_xi_CD_e_v; // Gain for xi_CD
        float _e_alt, _e_vx, _e_vy; // Errors needed for the estimators
        float _kt, _km; // Motor model

        // Math
        float _a, _b, _e;

        // Log
        std::ofstream _log;

    public:
        Quad_GNC(int, Sim *, Quad_Sensors *);
        Quad_GNC();
        ~Quad_GNC();

        void set_physical_variables(Eigen::Matrix3f, float, float);
        void set_motor_model(float, float);
        void set_attitude_gains(float, float, float);
        void set_control_gains(float, float, float, float);
        void set_xi_g_gains(float, float);
        void set_xi_CD_gains(float);

        void set_active_controller(Controller);

        void update(long t);
        Eigen::VectorXf get_X();
        Eigen::VectorXf get_V();
        Eigen::VectorXf get_attitude();
        Eigen::VectorXf get_gps();
        Eigen::VectorXf get_acc();

        void navigation_update();
        void set_yaw_d(float);
        void set_xyz_zero(float, float, float);
        void set_xyz(float, float, float);
        void set_v_2D_alt(float, float, float);
        void set_a_2D_alt(float, float, float);
        void set_a_ned(float, float, float);

        void control_att_lya(float, float, float, float);
        void control_xyz_ned_lya();
        void control_v_2D_alt_lya();
        void control_a_2D_alt_lya();
        void control_a_ned();
        void step_estimator_xi_g(float);
        void step_estimator_xi_CD(float);
        float get_xi_g();
        float get_xi_CD();

        void log(float);
};

#endif
