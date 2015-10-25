#include <iostream>

#include "sim.hh"
#include "flyingmachine.hh"

int main(int argc, char* argv[])
{
    std::string cfg;

    if(argc == 2){
        cfg = argv[1];
    }

    std::string ip_q1("127.0.0.1");
    int udp_xplane_in_q1 = 50000;
    int udp_xplane_out_q1 = 60001;

    Sim xp_q1(ip_q1, udp_xplane_in_q1, udp_xplane_out_q1, XPLANE);

    Guidance g_q1;
    Navigation n_q1;
    Control c_q1;

    GNC gnc_q1(&g_q1, &n_q1, &c_q1);

    Flyingmachine quad_1(&xp_q1, &gnc_q1);

    for(;;){
        quad_1.update(0);
    }

    return 0;
}
