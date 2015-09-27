#include "sim.hh"

Sim::Sim(std::string ip, int udp_port, Simulator simulator):
    _ip(ip),
    _udp_port(udp_port),
    _simulator(simulator)
{
}

Sim::~Sim()
{
}
