#ifndef SIM_HH
#define SIM_HH 1

#include <string>
#include <vector>
#include "./comm/udp_client_server.hh"

enum Simulator{
    XPLANE};

class Sim
{
    private:
        std::string _ip;
        Simulator _simulator;

        std::vector<char> _datagram;
        udp_server _server;
        udp_client _client;

        int _readDatagram();

    public:
        Sim(std::string, int, int, Simulator);
        ~Sim();

        void connect();
        void readFromSim();
};

#endif
