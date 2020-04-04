#include <iostream>
#include <vector>
#include <time.h>

#include "sim.hh"
#include "flyingmachine.hh"
#include "./quadrotor/quad_gnc.hh"
#include "./quadrotor/quad_sensors.hh"
#include "./formation/distance_formation.hh"
#include "./formation/position_formation.hh"
#include "./formation/bearing_formation.hh"

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

    int num_quads = 1;

    std::string q_ip("127.0.0.1");
    int q_udp_xplane_in[1] = {50000};
    int q_udp_xplane_out[1] = {60001};

    std::vector<Flyingmachine> quads;
    std::vector<Quad_GNC*> quads_gnc;

    for(int i = 0; i < num_quads; i++){
        Sim *q_xp = 
            new Sim(q_ip, q_udp_xplane_in[i], q_udp_xplane_out[i], XPLANE);
        Quad_Sensors *q_sen = new Quad_Sensors(i+1, q_xp);
        Quad_GNC *q_gnc = new Quad_GNC(i+1, q_xp, q_sen);

        q_gnc->set_physical_variables(J, m, l);
        q_gnc->set_motor_model(kt, km);
        q_gnc->set_attitude_gains(kp, kq, kr);
        q_gnc->set_control_gains(k_xy, k_vxy, k_vz, k_alt);
        q_gnc->set_xi_g_gains(k_xi_g_v, k_xi_g_e_alt);
        q_gnc->set_xi_CD_gains(k_xi_CD_e_v);

        Flyingmachine q(q_xp, dynamic_cast<Sensors*>(q_sen),
                dynamic_cast<GNC*>(q_gnc));

        quads.push_back(q);
        quads_gnc.push_back(q_gnc);
    }

    // Setting control
    for (std::vector<Quad_GNC*>::iterator it = quads_gnc.begin();
            it != quads_gnc.end(); ++it){
        (*it)->set_xyz_zero(0.824756, 0.198016, 576.5);
        (*it)->set_yaw_d(M_PI);
        (*it)->set_active_controller(V_2D_ALT);
        (*it)->set_v_2D_alt(0, 0, -600);
    }


    for(;;){
        clock_gettime(CLOCK_REALTIME, &ts);
        last_step_time = ts.tv_nsec;

        for (std::vector<Flyingmachine>::iterator it = quads.begin();
                it != quads.end(); ++it)
            it->update(time);

        time += dt;

        clock_gettime(CLOCK_REALTIME, &ts);
        tsleep.tv_nsec = dt - (ts.tv_nsec - last_step_time);
        nanosleep(&tsleep, NULL);
    }

    return 0;
}
