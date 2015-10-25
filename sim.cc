#include <iostream>
#include <string>

#include "sim.hh"
#include "./comm/udp_client_server.hh"
#include "./XPlane/XPdata.hh"

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

int Sim::_readDatagram(){
    int readBytes = 0;

    _datagram.resize(1000, 0);
    readBytes = _server.recv(&*_datagram.begin(), _datagram.size());
    if (readBytes < 0)
        return readBytes;
    _datagram.resize(readBytes);

    std::cout << "Received bytes: " << readBytes << std::endl;

    return readBytes;
}

void Sim::readFromSim(){
    if(_simulator == XPLANE){
        XPdataVector v;

        _readDatagram();
        int isData = 1;
        const char *data= "DATA";

        std::vector<char>::iterator i(_datagram.begin());
        std::vector<char>::iterator ii(_datagram.end());

        for(int iii = 0; iii < 4; ++iii)
            if (*(i+iii) != data[iii])
                isData = 0;

        if(isData){
            std::tr1::shared_ptr<XPdata> _xpd;
            i+=5;

            while(i != (ii)){
                _xpd.reset(XPdata::create(i));
                if(_xpd)
                    v.push_back(_xpd);
            }
        }
    }
}
