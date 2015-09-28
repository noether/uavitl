#include <iostream>
#include <string>

#include "sim.hh"
#include "./comm/udp_client_server.hh"

Sim::Sim(std::string ip, int udp_port_in,
        int udp_port_out, Simulator simulator):
    _ip(ip),
    _simulator(simulator),
    _server(udp_server(_ip.c_str(), udp_port_out)),
    _client(udp_client(_ip.c_str(), udp_port_in))
{
}

Sim::~Sim()
{
}

void Sim::connect(){
    _server.connect();
    _client.connect();
}

int Sim::readDatagram(){
    int readBytes = 0;

    _datagram.resize(100, 0);
    // TODO check for timeouts
    readBytes = _server.recv(&*_datagram.begin(), _datagram.size());
    if (readBytes < 0)
        return readBytes;
    _datagram.resize(readBytes);

    std::cout << "Received bytes: " << readBytes << std::endl;

    return readBytes;
}
