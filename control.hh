#ifndef CONTROL_HH
#define CONTROL_HH 1

#include "Eigen/Core"

#include "sim.hh"
#include "navigation.hh"
#include "guidance.hh"

class Control
{
    private:
        Sim *_sim;
        Navigation *_nav;
        Guidance *_gui;

        float _kf;
        float _dkf;
        float _km;

        Eigen::Matrix4f uf_to_u;

    public:
        Control();
        Control(Sim *, Navigation *, Guidance *);
        ~Control();

        void update();
};

#endif
