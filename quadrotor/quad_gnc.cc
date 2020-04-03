#include <boost/filesystem.hpp>
#include <iostream>
#include <fstream>
#include <time.h>
#include <cmath>
#include <string>
#include "Eigen/Core"
#include "Eigen/LU"
#include "quad_gnc.hh"
#include "../sim.hh"

template <typename T> int sgn(T val) {
    return (T(0) < val) - (val < T(0));
}

Quad_GNC::Quad_GNC():
    GNC(-1, NULL),
    _sen(NULL),
    _roll(-999), _pitch(-999), _yaw(-999),
    _ax(-999), _ay(-999), _az(-999),
    _vn(-999), _ve(-999), _vd(-999),
    _x(-999), _y(-999), _z(-999),
    _alt(-999),
    _p(-999), _q(-999), _r(-999),
    _m(-999), _l(-999),
    _roll_d(-999), _pitch_d(-999), _yaw_d(-999),
    _an_d(-999), _ae_d(-999), _ad_d(-999),
    _vn_d(-999), _ve_d(-999), _vd_d(-999),
    _x_d(-999), _y_d(-999), _z_d(-999),
    _alt_d(-999),
    _controller(NO_CONTROLLER),
    _kp(0), _kq(0), _kr(0), _k_xy(0), _k_vxy(0),
     _k_vz(0), _k_alt(0),
    _xi_g(-999), _xi_CD(-999), _k_xi_g_v(0),
    _k_xi_g_e_alt(0), _k_xi_CD_e_v(0),
    _e_alt(0), _e_vx(0), _e_vy(0),
    _kt(0), _km(0)
{
    _w_to_Tlmn << 0, 0, 0, 0,
                  0, 0, 0, 0,
                  0, 0, 0, 0,
                  0, 0, 0, 0;

    _Tlmn_to_w = _w_to_Tlmn;

    _J << 0, 0, 0,
          0, 0, 0,
          0, 0, 0;

    _a = 6378137.0;
    _b = 6356752;
    _e = sqrtf(_a*_a - _b*_b) / _a;
}

Quad_GNC::Quad_GNC(int id, Sim *sim, Quad_Sensors *sen):
    GNC(id, sim),
    _sen(sen),
    _roll(-999), _pitch(-999), _yaw(-999),
    _ax(-999), _ay(-999), _az(-999),
    _vn(-999), _ve(-999), _vd(-999),
    _x(-999), _y(-999), _z(-999),
    _alt(-999),
    _p(-999), _q(-999), _r(-999),
    _m(-999), _l(-999),
    _roll_d(-999), _pitch_d(-999), _yaw_d(-999),
    _an_d(-999), _ae_d(-999), _ad_d(-999),
    _vn_d(-999), _ve_d(-999), _vd_d(-999),
    _x_d(-999), _y_d(-999), _z_d(-999),
    _alt_d(-999),
    _controller(NO_CONTROLLER),
    _kp(0), _kq(0), _kr(0), _k_xy(0), _k_vxy(0),
    _k_vz(0), _k_alt(0),
    _xi_g(9.8), _xi_CD(0), _k_xi_g_v(0),
    _k_xi_g_e_alt(0), _k_xi_CD_e_v(0),
    _e_alt(0), _e_vx(0), _e_vy(0),
    _kt(0), _km(0)
{
  //  _w_to_Tlmn << -_kt,    -_kt,    -_kt,    -_kt,
  //                   0, -_l*_kt,       0,  _l*_kt,
  //              _l*_kt,       0, -_l*_kt,       0,
  //                -_km,    -_km,    -_km,    -_km;

  //  _Tlmn_to_w = _w_to_Tlmn;

    _J << 0, 0, 0,
          0, 0, 0,
          0, 0, 0;

    _a = 6378137.0;
    _b = 6356752;
    _e = sqrtf(_a*_a - _b*_b) / _a;

    time_t rawtime;
    struct tm * timeinfo;
    char buffer [80];

    time (&rawtime);
    timeinfo = localtime (&rawtime);
    strftime (buffer, 80, "%F-%H%M", timeinfo);
    std::string dir_path("./log/");
    dir_path.append(buffer);

    boost::filesystem::path dir(dir_path.c_str());
    if(!boost::filesystem::is_directory(dir))
        boost::filesystem::create_directory(dir);

    dir_path.append("/log_gnc_");
    dir_path.append(std::to_string(_id));
    dir_path.append(".txt");

    _log.open(dir_path);
}

Quad_GNC::~Quad_GNC()
{
}

void Quad_GNC::set_physical_variables(Eigen::Matrix3f J, float m, float l)
{
    _J = J;
    _m = m;
    _l = l;
}

void Quad_GNC::set_motor_model(float kt, float km)
{
    _kt = kt;
    _km = km;

    _w_to_Tlmn << -_kt,    -_kt,    -_kt,    -_kt,
                     0, -_l*_kt,       0,  _l*_kt,
                _l*_kt,       0, -_l*_kt,       0,
                  -_km,    _km,    -_km,    _km;

    _Tlmn_to_w = _w_to_Tlmn.inverse();
}

void Quad_GNC::set_attitude_gains(float kp, float kq, float kr)
{
    _kp = kp;
    _kq = kq;
    _kr = kr;
}

void Quad_GNC::set_control_gains(float k_xy,
        float k_vxy, float k_vz, float k_alt)
{
    _k_xy = k_xy;
    _k_vxy = k_vxy;
    _k_vz = k_vz;
    _k_alt = k_alt;
}

void Quad_GNC::set_xi_g_gains(float k_xi_g_v, float k_xi_g_e_alt)
{
    _k_xi_g_v = k_xi_g_v;
    _k_xi_g_e_alt = k_xi_g_e_alt;
}

void Quad_GNC::set_xi_CD_gains(float k_xi_CD_e_v)
{
    _k_xi_CD_e_v = k_xi_CD_e_v;
}


void Quad_GNC::set_active_controller(Controller c)
{
    _controller = c;
}

void Quad_GNC::update(long t)
{
    t++;
    float dt = 0.0166;

    // Navigation states
    navigation_update();

    // Guidance
    // No internal guidance

    // Control
    switch(_controller)
    {
        case XYZ:
            control_xyz_ned_lya();
            step_estimator_xi_g(dt);
            break;
        case V_2D_ALT:
            control_v_2D_alt_lya();
            step_estimator_xi_g(dt);
            step_estimator_xi_CD(dt);
            break;
        case A_2D_ALT:
            control_a_2D_alt_lya();
            step_estimator_xi_g(dt);
            break;
        case A_3D:
            control_a_ned();
            break;
        default:
            break;
    }
}

Eigen::VectorXf Quad_GNC::get_X()
{
    Eigen::VectorXf X(3);
    X << _x, _y, _z;
    return X;
}

Eigen::VectorXf Quad_GNC::get_V()
{
    Eigen::VectorXf V(3);
    V << _vn, _ve, _vd;
    return V;
}

Eigen::VectorXf Quad_GNC::get_attitude()
{
    Eigen::VectorXf att(3);
    att << _roll, _pitch, _yaw;
    return att;
}

Eigen::VectorXf Quad_GNC::get_gps()
{
    Eigen::VectorXf gps(3);
    gps << _lon, _lat, _alt;
    return gps;
}

Eigen::VectorXf Quad_GNC::get_acc()
{
    Eigen::VectorXf acc(3);
    acc << _ax, _ay, _az;
    return acc;
}

void Quad_GNC::navigation_update()
{
    // Attitude estimation
    // TODO for now we take the attitude from the simulator
    _roll = _sim->get_roll();
    _pitch = _sim->get_pitch();
    _yaw = _sim->get_yaw();

    // Accelerometers estimation
    float a_body[3];
    _sen->get_accelerometers(a_body);
    _ax = a_body[0];
    _ay = a_body[1];
    _az = a_body[2];

    // Velocity estimation
    float v_enu[3];
    _sen->get_gps_v_enu(v_enu);
    _ve = v_enu[0];
    _vn = v_enu[1];
    _vd = -v_enu[2];

    // Angular velocity estimation
    float pqr[3];
    _sen->get_gyroscopes(pqr);
    _p = pqr[0];
    _q = pqr[1];
    _r = pqr[2];

    // Altitude (msl)
    float coord[3];
    _sen->get_gps_coord(coord);
    _lat = coord[0];
    _lon = coord[1];
    _alt = coord[2];
    
    // XYZ estimation wrt Ground Station
    _xyz_wrt_xyz_zero(_lat, _lon, _alt);
}

Eigen::Matrix3f Quad_GNC::_get_Body_to_Nav()
{
    Eigen::Matrix3f R;

    float cthe = cosf(_pitch);
    float sthe = sinf(_pitch);
    float cphi = cosf(_roll);
    float sphi = sinf(_roll);
    float cpsi = cosf(_yaw);
    float spsi = sinf(_yaw);

    R << cthe*cpsi, cthe*spsi, -sthe,
        -cphi*spsi + sphi*sthe*cpsi, cphi*cpsi + sphi*sthe*spsi, sphi*cthe,
        sphi*spsi + cphi*sthe*cpsi, -sphi*cpsi + cphi*sthe*spsi, cphi*cthe;

    return R.transpose();
}

void Quad_GNC::set_yaw_d(float yaw_d)
{
    _yaw_d = yaw_d;
}

void Quad_GNC::set_xyz_zero(float lat_zero, 
        float lon_zero, float alt_zero)
{
    float N = _a / sqrtf(1 - (_e*_e * sinf(lat_zero)*sinf(lat_zero)));
    
    _x_zero = (N + alt_zero)*cosf(lat_zero)*cosf(lon_zero);
    _y_zero = (N + alt_zero)*cosf(lat_zero)*sinf(lon_zero);
    _z_zero = (N*(1 - (_e*_e)) + alt_zero)*sinf(lat_zero);

    float sp = sinf(lat_zero);
    float cp = cosf(lat_zero);
    float sl = sinf(lon_zero);
    float cl = cosf(lon_zero);

    _ECEF_to_Nav << -sp*cl, -sp*sl,  cp,
                       -sl,     cl,   0,
                    -cp*cl, -cp*sl, -sp;

}

void Quad_GNC::set_xyz(float x_d, float y_d, float z_d)
{
    _x_d = x_d;
    _y_d = y_d;
    _z_d = z_d;
}

void Quad_GNC::set_v_2D_alt(float vn_d, float ve_d, float alt_d)
{
    _vn_d = vn_d;
    _ve_d = ve_d;
    _alt_d = alt_d;
}

void Quad_GNC::set_a_2D_alt(float an_d, float ae_d, float alt_d)
{
    _an_d = an_d;
    _ae_d = ae_d;
    _alt_d = alt_d;
}

void Quad_GNC::set_a_ned(float an_d, float ae_d, float ad_d)
{
    _an_d = an_d;
    _ae_d = ae_d;
    _ad_d = ad_d;
}

void Quad_GNC::control_att_lya(float phi_d, float the_d, float yaw_d,
        float T_d)
{

    // Saturation (safety)
    if(phi_d < -10*M_PI/180 || phi_d > 10*M_PI/180)
        phi_d = 10*M_PI/180*sgn(phi_d);

    if(the_d < -10*M_PI/180 || the_d > 10*M_PI/180)
        the_d = 10*M_PI/180*sgn(the_d);


    // Navigation data
    float Jxx = _J(0, 0);
    float Jyy = _J(1, 1);
    float Jzz = _J(2, 2);

    // Control errors
    float ephi = _roll - phi_d;
    float ethe = _pitch - the_d;
    float epsi = _yaw - yaw_d;

    // Desired moments
    float l_d = -Jxx*(100*ephi + _kp*_p) - (Jyy-Jzz)*_q*_r;
    float m_d = -Jyy*(100*ethe + _kq*_q) - (Jzz-Jxx)*_r*_p;
    float n_d = -Jzz*(10*epsi + _kr*_r);

    // Desired angular velocities for the motors
    Eigen::Vector4f Tlmn_d;
    Tlmn_d << T_d, l_d, m_d, n_d;
    Eigen::Vector4f w_sq = _Tlmn_to_w * Tlmn_d;

    // XPlane needs of a normalization factor, inputs between 0 and 1
    // It depends on your gains !!
    Eigen::Array4f u = w_sq.array().sqrt() / 500;

    if(std::isnan(u(0)+u(1)+u(2)+u(3))){
        u.setZero();
        std::cout << "Control input contains NaN!" << std::endl;
    }

    int i;
    for (i = 0; i < 4; i++){
        if (u(i) > 1)
            u(i) = 1;
        else if (u(i) < 0)
            u(i) = 0;
    }

    _sim->set_tc(u(0), u(1), u(2), u(3),
            0.0, 0.0, 0.0, 0.0);
}

void Quad_GNC::control_xyz_ned_lya()
{
    // Control errors
    float ex = _x - _x_d;
    float ey = _y - _y_d;
    float ez = _z - _z_d;

    _e_alt = ez; // For the gravity estimator

    // Desired accelerations
    float ax_d = -_k_xy*ex -_k_vxy*_vn;
    float ay_d = -_k_xy*ey -_k_vxy*_ve;
    float az_d = -_xi_g -_k_alt*ez -_k_vz*_vd;

    // Desired attitude and thrust
    float phi_d =  (ax_d*sinf(_yaw) - ay_d*cosf(_yaw))/az_d;
    float the_d =  (ax_d*cosf(_yaw) + ay_d*sinf(_yaw))/az_d;
    float T_d = az_d*_m;

    control_att_lya(phi_d, the_d, _yaw_d, T_d);
}

void Quad_GNC::control_v_2D_alt_lya()
{
    // Control errors
    float e_alt = -_alt - _alt_d;
    float e_vx = _vn - _vn_d;
    float e_vy = _ve - _ve_d;

    _e_alt = e_alt; // For the gravity estimator
    _e_vx = e_vx;  // For the CD estimation
    _e_vy = e_vy;  // For the CD estimation

    // Desired accelerations
    float v_norm = sqrt(_vn*_vn + _ve*_ve);
    float ax_d = _xi_CD*v_norm*_vn - _k_vxy*e_vx;
    float ay_d = _xi_CD*v_norm*_ve - _k_vxy*e_vy;
    float az_d = -_xi_g - _k_alt*e_alt - _k_vz*_vd;

    // Desired attitude and thrust
    float phi_d =  (ax_d*sinf(_yaw) - ay_d*cosf(_yaw))/az_d;
    float the_d =  (ax_d*cosf(_yaw) + ay_d*sinf(_yaw))/az_d;
    float T_d = az_d*_m;


    control_att_lya(phi_d, the_d, _yaw_d, T_d);
}

void Quad_GNC::control_a_2D_alt_lya()
{
    // Control errors
    float e_alt = -_alt - _alt_d;

    _e_alt = e_alt; // For the gravity estimator

    // Desired accelerations
    float ax_d = _an_d;
    float ay_d = _ae_d;
    float az_d = -_xi_g  - _k_alt*e_alt - _k_vz*_vd;


    // Desired attitude and thrust
    float phi_d =  (ax_d*sinf(_yaw) - ay_d*cosf(_yaw))/az_d;
    float the_d =  (ax_d*cosf(_yaw) + ay_d*sinf(_yaw))/az_d;
    float T_d = az_d*_m;


    control_att_lya(phi_d, the_d, _yaw_d, T_d);
}

void Quad_GNC::control_a_ned()
{
    // Desired accelerations
    float ax_d = _an_d;
    float ay_d = _ae_d;
    float az_d = _ad_d - 9.82;

    // Desired attitude and thrust
    float phi_d =  (ax_d*sinf(_yaw) - ay_d*cosf(_yaw))/az_d;
    float the_d =  (ax_d*cosf(_yaw) + ay_d*sinf(_yaw))/az_d;
    float T_d = az_d*_m;

    control_att_lya(phi_d, the_d, _yaw_d, T_d);
}

void Quad_GNC::step_estimator_xi_g(float dt)
{
    // Euler integration
    // Gravity estimator
    _xi_g = _xi_g + (_k_xi_g_v*_vd + _k_xi_g_e_alt*_e_alt)*dt;
}

float Quad_GNC::get_xi_g(void)
{
    return _xi_g;
}

void Quad_GNC::step_estimator_xi_CD(float dt)
{
    // Euler integration
    // CD estimator
    float v_norm = sqrt(_vn*_vn + _ve*_ve);
    _xi_CD = _xi_CD - (_k_xi_CD_e_v*v_norm*(_e_vx*_vn + _e_vy*_ve))*dt;
}

float Quad_GNC::get_xi_CD(void)
{
    return _xi_CD;
}


void Quad_GNC::_xyz_wrt_xyz_zero(float lat, float lon, float alt)
{
    float N = _a / sqrtf(1 - (_e*_e * sinf(lat)*sinf(lat)));

    float x_ecef = (N + alt)*cosf(lat)*cosf(lon);
    float y_ecef = (N + alt)*cosf(lat)*sinf(lon);
    float z_ecef = (N*(1 - (_e*_e)) + alt)*sinf(lat);

    float _xe = x_ecef - _x_zero;
    float _ye = y_ecef - _y_zero;
    float _ze = z_ecef - _z_zero;

    Eigen::Vector3f Xe;
    Xe << _xe, _ye, _ze;

    Eigen::Vector3f X = _ECEF_to_Nav * Xe;
    _x = X(0);
    _y = X(1);
    _z = X(2);
}

void Quad_GNC::log(float t)
{
    _log << t << " " << get_X().transpose() << " " << get_V().transpose() 
        << " " << get_attitude().transpose() << " " << get_gps().transpose() 
        << " " << get_xi_g() << " " << get_xi_CD()
        << " " << (_get_Body_to_Nav() * get_acc()).transpose() << std::endl;
}
