#include <iostream>

#include "sim.hh"
#include "flyingmachine.hh"

int main(int argc, char* argv[])
{

    std::string cfg;

    if(argc == 1)
    {
        cfg = argv[1];
    }

    std::string ip("127.0.0.1");
    int udp_port = 49000;

    Sim xp(ip, udp_port, XPLANE);
    Flyingmachine plane(xp);

    return 0;
}
