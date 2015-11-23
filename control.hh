#ifndef CONTROL_HH
#define CONTROL_HH 1

#include "sim.hh"
#include "navigation.hh"
#include "guidance.hh"

class Control
{
    private:
        Sim *_sim;
        Navigation *_nav;
        Guidance *_gui;

    public:
        Control();
        Control(Sim *, Navigation *, Guidance *);
        ~Control();

        void update();
};

#endif
