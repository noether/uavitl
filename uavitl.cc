#include <iostream>

#include "sim.hh"
#include "flyingmachine.hh"

int main(int argc, char* argv[])
{
    std::string cfg;

    if(argc == 1){
        cfg = argv[0];
    }

    std::string ip("127.0.0.1");
    int udp_xplane_in = 40000;
    int udp_xplane_out = 49003;

    Sim xp(ip, udp_xplane_in, udp_xplane_out, XPLANE);

    Guidance g;
    Navigation n;
    Control c;

    GNC gnc(&g, &n, &c);

    Flyingmachine plane(&xp, &gnc);

    for(;;){
        plane.update(0);
    }

    return 0;
}
