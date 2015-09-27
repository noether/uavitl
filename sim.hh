#ifndef SIM_HH
#define SIM_HH 1

#include <string>

enum Simulator{
    XPLANE};

class Sim
{
    private:
        std::string _ip;
        int _udp_port;
        Simulator _simulator;


    public:
        Sim(std::string, int, Simulator);
        ~Sim();

};

#endif
