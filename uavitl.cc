#include <iostream>
#include <time.h>

#include "sim.hh"
#include "flyingmachine.hh"
#include "./quadrotor/quad_gnc.hh"
#include "./quadrotor/quad_sensors.hh"

int main(int argc, char* argv[])
{
    std::string cfg;

    if(argc == 2){
        cfg = argv[1];
    }

    timespec ts;
    timespec tsleep;
    tsleep.tv_sec = 0;
    int last_step_time = -1;
    long dt = 166e5; // nanoseconds
    long time = 0;

    Eigen::Matrix3f J;
    J << 7.5e-3,      0,      0,
              0, 7.5e-3,      0,
              0,      0, 1.3e-2;
    float m = 1;
    float l = 0.23;
    //float kt = 3.13e-5;
    float kt = 2.99e-5;
    float km = 7.5e-7;
    float kp = 4;
    float kq = 4;
    float kr = 4;
    float k_xy = 1e-1;
    float k_vxy = 1;
    float k_vz = 1;
    float k_alt = 1e-1;
    float k_xi_g_v = 5e-1;
    float k_xi_g_e_alt = 1e-1;
    float k_xi_CD_e_v = 1e-3;

    std::string q1_ip("127.0.0.1");
    int q1_udp_xplane_in = 50000;
    int q1_udp_xplane_out = 60001;

    Sim *q1_xp = new Sim(q1_ip, q1_udp_xplane_in, q1_udp_xplane_out, XPLANE);
    Quad_Sensors *q1_sen = new Quad_Sensors(q1_xp);
    Quad_GNC *q1_gnc = new Quad_GNC(q1_xp, q1_sen);

    q1_gnc->set_physical_variables(J, m, l);
    q1_gnc->set_motor_model(kt, km);
    q1_gnc->set_attitude_gains(kp, kq, kr);

    q1_gnc->set_control_gains(k_xy, k_vxy, k_vz, k_alt);
    q1_gnc->set_xi_g_gains(k_xi_g_v, k_xi_g_e_alt);
    q1_gnc->set_xi_CD_gains(k_xi_CD_e_v);

    Flyingmachine q1(q1_xp, dynamic_cast<Sensors*>(q1_sen),
            dynamic_cast<GNC*>(q1_gnc));

    q1_gnc->set_xyz_zero(0.824756, 0.198016, 576.5);
    q1_gnc->set_yaw_d(M_PI/4);
    q1_gnc->set_active_controller(XYZ);
    q1_gnc->set_xyz(-10, -2, -10);
    
 //   q1_gnc->set_active_controller(V_2D_ALT);
 //   q1_gnc->set_v_2D_alt(0, 0, -600);


    std::string q2_ip("127.0.0.1");
    int q2_udp_xplane_in = 51000;
    int q2_udp_xplane_out = 61001;

    Sim *q2_xp = new Sim(q2_ip, q2_udp_xplane_in, q2_udp_xplane_out, XPLANE);
    Quad_Sensors *q2_sen = new Quad_Sensors(q2_xp);
    Quad_GNC *q2_gnc = new Quad_GNC(q2_xp, q2_sen);

    q2_gnc->set_physical_variables(J, m, l);
    q2_gnc->set_motor_model(kt, km);
    q2_gnc->set_attitude_gains(kp, kq, kr);

    q2_gnc->set_control_gains(k_xy, k_vxy, k_vz, k_alt);
    q2_gnc->set_xi_g_gains(k_xi_g_v, k_xi_g_e_alt);
    q2_gnc->set_xi_CD_gains(k_xi_CD_e_v);

    Flyingmachine q2(q2_xp, dynamic_cast<Sensors*>(q2_sen),
            dynamic_cast<GNC*>(q2_gnc));

    q2_gnc->set_xyz_zero(0.824756, 0.198016, 576.5);
    q2_gnc->set_yaw_d(M_PI/4);
    q2_gnc->set_active_controller(A_2D_ALT);
    q2_gnc->set_a_2D_alt(0, 0, -600);

    for(;;)
    {
        clock_gettime(CLOCK_REALTIME, &ts);
        last_step_time = ts.tv_nsec;

        q1.update(time);
     //   q2.update(time);

        time += dt;
     //   if(time >= 180e9)
     //       break;

        clock_gettime(CLOCK_REALTIME, &ts);
        tsleep.tv_nsec = dt - (ts.tv_nsec - last_step_time);
     //   std::cout << "Time for sleeping: "
     //       << dt - (ts.tv_nsec - last_step_time) << std::endl;
        nanosleep(&tsleep, NULL);
    }

    return 0;
}
