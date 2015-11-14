#include <iostream>
#include <time.h>

#include "sim.hh"
#include "flyingmachine.hh"
#include "guidance.hh"
#include "navigation.hh"
#include "control.hh"
#include "sensors.hh"

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
    long dt = 1e9;
    long time = 0;

    std::string ip_q1("127.0.0.1");
    int udp_xplane_in_q1 = 50000;
    int udp_xplane_out_q1 = 60001;
    Sim xp_q1(ip_q1, udp_xplane_in_q1, udp_xplane_out_q1, XPLANE);
    Sensors sen_q1(&xp_q1);
    Guidance g_q1;
    Navigation n_q1(&xp_q1, &sen_q1);
    Control c_q1(&xp_q1, &n_q1);
    GNC gnc_q1(&g_q1, &n_q1, &c_q1);

    Flyingmachine quad_1(&xp_q1, &gnc_q1, &sen_q1);

    for(;;)
    {
        clock_gettime(CLOCK_REALTIME, &ts);
        last_step_time = ts.tv_nsec;

        quad_1.update(time);

        time += dt;
        std::cout << time << " ns" << std::endl;
        if(time >= 1e10)
            break;

        clock_gettime(CLOCK_REALTIME, &ts);
        tsleep.tv_nsec = dt - (ts.tv_nsec - last_step_time);
        nanosleep(&tsleep, NULL);
    }

    return 0;
}
