#ifndef CONTROL_HH
#define CONTROL_HH 1

#include "sim.hh"
#include "navigation.hh"

class Control
{
    private:
        Sim *_sim;
        Navigation *_nav;

    public:
        Control();
        Control(Sim *, Navigation *);
        ~Control();

        void update();
};

#endif
