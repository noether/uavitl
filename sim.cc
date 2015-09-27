#include <iostream>
#include <string>

#include "sim.hh"
#include "./comm/udp_client_server.hh"

Sim::Sim(std::string ip, int udp_port_in,
        int udp_port_out, Simulator simulator):
    _ip(ip),
    _simulator(simulator)
{
    _server = udp_server(ip.c_str(), udp_port_out);
    _client = udp_client(ip.c_str(), udp_port_in);
}

Sim::~Sim()
{
}

int Sim::readDatagram(){
    int readBytes = 0;

    _datagram.resize(100, 0);
    // TODO check for timeouts
    readBytes = _server.recv(&*_datagram.begin(), _datagram.size());
    _datagram.resize(readBytes);

    std::cout << "Recevied bytes: " << readBytes << std::endl;

    return readBytes;
}
