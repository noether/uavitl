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

        // Quad setup
        Eigen::Matrix4f _w_to_Tlmn;
        Eigen::Matrix4f _Tlmn_to_w;

        // Gains and variables for the attitude controller
        float _kp;
        float _kq;
        float _kr;
        float _l_d;
        float _m_d;
        float _n_d;

    public:
        Control();
        Control(Sim *, Navigation *, Guidance *);
        ~Control();

        void control_att();
        void control_motors();

        void update();
};

#endif
