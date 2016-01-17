#include "Eigen/Core"
#include "Eigen/LU"
#include "quad_gnc.hh"
#include "../sim.hh"

Quad_GNC::Quad_GNC():
    GNC(NULL),
    _sen(NULL),
    _roll(-999), _pitch(-999), _yaw(-999),
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

Quad_GNC::Quad_GNC(Sim *sim, Quad_Sensors *sen):
    GNC(sim),
    _sen(sen),
    _roll(-999), _pitch(-999), _yaw(-999),
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
            control_a_ned_lya();
            break;
        default:
            break;
    }
}

void Quad_GNC::navigation_update()
{
    // Attitude estimation
    // TODO for now we take the attitude from the simulator
    _roll = _sim->get_roll();
    _pitch = _sim->get_pitch();
    _yaw = _sim->get_yaw();

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
    _alt = coord[2];
    
    // XYZ estimation wrt Ground Station
    _xyz_wrt_xyz_zero(coord[0], coord[1], coord[2]);
    std::cout << "Lat: " << coord[0] << " Lon: " << coord[1] << 
        " Alt: " << coord[2] << std::endl;
    std::cout << "XYZ: " << _x << " " << _y << " " << _z << std::endl;
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
    // Navigation data
    float Jxx = _J(0, 0);
    float Jyy = _J(1, 1);
    float Jzz = _J(2, 2);

    // Control errors
    float ephi = _roll - phi_d;
    float ethe = _pitch - the_d;
    float epsi = _yaw - yaw_d;

    std::cout << "Error roll: " << ephi << std::endl;
    std::cout << "Error pitch: " << ethe << std::endl;
    std::cout << "Error yaw: " << epsi << std::endl;

    // Desired moments
    float l_d = -Jxx*(100*ephi + _kp*_p) - (Jyy-Jzz)*_q*_r;
    float m_d = -Jyy*(100*ethe + _kq*_q) - (Jzz-Jxx)*_r*_p;
    float n_d = -Jzz*(10*epsi + _kr*_r);

    std::cout << "Desired l: " << l_d << std::endl;
    std::cout << "Desired m: " << m_d << std::endl;
    std::cout << "Desired n: " << n_d << std::endl;

    // Desired angular velocities for the motors
    Eigen::Vector4f Tlmn_d;
    Tlmn_d << T_d, l_d, m_d, n_d;
    Eigen::Vector4f w_sq = _Tlmn_to_w * Tlmn_d;

    // XPlane needs of a normalization factor, inputs between 0 and 1
    // It depends on your gains !!
    Eigen::Array4f u = w_sq.array().sqrt() / 500;
    
    int i;
    for (i = 0; i < 4; i++){
        std::cout << "U(" << i <<") = " << u(i) << std::endl;
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

    std::cout << "Error X: " << ex << std::endl;
    std::cout << "Error Y: " << ey << std::endl;
    std::cout << "Error Z: " << ez << std::endl;
 
    std::cout << "xi_g: " << _xi_g << std::endl;

    // Desired accelerations
    float ax_d = -_k_xy*ex -_k_vxy*_vn;
    float ay_d = -_k_xy*ey -_k_vxy*_ve;
    float az_d = -_xi_g -_k_alt*ez -_k_vz*_vd;

    // Desired attitude and thrust
    float phi_d = -(ay_d*cosf(_yaw) - ax_d*cosf(_yaw))/az_d;
    float the_d =  (ax_d*cosf(_yaw) + ay_d*cosf(_yaw))/az_d;
    float T_d = az_d*_m;

    control_att_lya(phi_d, the_d, _yaw_d, T_d);
}

void Quad_GNC::control_v_2D_alt_lya()
{
    // Control errors
    float e_alt = -_alt - _alt_d;
    float e_vx = _vn - _vn_d;
    float e_vy = _ve - _ve_d;

    std::cout << "Error altitude: " << e_alt << std::endl;

    _e_alt = e_alt; // For the gravity estimator
    _e_vx = e_vx;  // For the CD estimation
    _e_vy = e_vy;  // For the CD estimation

    std::cout << "Error Vx: " << _e_vx << std::endl;
    std::cout << "Error Vy: " << _e_vy << std::endl;

    std::cout << "xi_g: " << _xi_g << std::endl;
    std::cout << "xi_CD: " << _xi_CD << std::endl;

    // Desired accelerations
    float v_norm = sqrt(_vn*_vn + _ve*_ve);
    float ax_d = _xi_CD*v_norm*_vn - _k_vxy*e_vx;
    float ay_d = _xi_CD*v_norm*_ve - _k_vxy*e_vy;
    float az_d = -_xi_g - _k_alt*e_alt - _k_vz*_vd;

    std::cout << "Desired ax: " << ax_d << std::endl;
    std::cout << "Desired ay: " << ay_d << std::endl;
    std::cout << "Desired az: " << az_d << std::endl;

    // Desired attitude and thrust
    float phi_d = -(ay_d*cosf(_yaw) - ax_d*cosf(_yaw))/az_d;
    float the_d =  (ax_d*cosf(_yaw) + ay_d*cosf(_yaw))/az_d;
    float T_d = az_d*_m;

    std::cout << "Desired roll: " << phi_d << std::endl;
    std::cout << "Desired pitch: " << the_d << std::endl;
    std::cout << "Desired yaw: " << _yaw_d << std::endl;
    std::cout << "Desired thrust: " << T_d << std::endl;

    control_att_lya(phi_d, the_d, _yaw_d, T_d);
}

void Quad_GNC::control_a_2D_alt_lya()
{
    // Control errors
    float e_alt = -_alt - _alt_d;

    std::cout << "Error altitude: " << e_alt << std::endl;

    _e_alt = e_alt; // For the gravity estimator

    // Desired accelerations
    float ax_d = _an_d;
    float ay_d = _ae_d;
    float az_d = -_xi_g  - _k_alt*e_alt - _k_vz*_vd;

    std::cout << "xi_g: " << _xi_g << std::endl;

    // Desired attitude and thrust
    float phi_d = -(ay_d*cosf(_yaw) - ax_d*cosf(_yaw))/az_d;
    float the_d =  (ax_d*cosf(_yaw) + ay_d*cosf(_yaw))/az_d;
    float T_d = az_d*_m;

    std::cout << "Desired roll: " << phi_d << std::endl;
    std::cout << "Desired pitch: " << the_d << std::endl;
    std::cout << "Desired yaw: " << _yaw_d << std::endl;
    std::cout << "Desired thrust: " << T_d << std::endl;

    control_att_lya(phi_d, the_d, _yaw_d, T_d);
}

void Quad_GNC::control_a_ned_lya()
{
    // Desired accelerations
    float ax_d = _an_d;
    float ay_d = _ae_d;
    float az_d = _ad_d;

    // Desired attitude and thrust
    float phi_d = -(ay_d*cosf(_yaw) - ax_d*cosf(_yaw))/az_d;
    float the_d =  (ax_d*cosf(_yaw) + ay_d*cosf(_yaw))/az_d;
    float T_d = az_d*_m;

    control_att_lya(phi_d, the_d, _yaw_d, T_d);
}

void Quad_GNC::step_estimator_xi_g(float dt)
{
    // Euler integration
    // Gravity estimator
    _xi_g = _xi_g + (_k_xi_g_v*_vd + _k_xi_g_e_alt*_e_alt)*dt;
}

void Quad_GNC::step_estimator_xi_CD(float dt)
{
    // Euler integration
    // CD estimator
    float v_norm = sqrt(_vn*_vn + _ve*_ve);
    _xi_CD = _xi_CD - (_k_xi_CD_e_v*v_norm*(_e_vx*_vn + _e_vy*_ve))*dt;
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
