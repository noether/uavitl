#ifndef GUIDANCE_HH
#define GUIDANCE_HH 1

#include "sim.hh"
#include "navigation.hh"

class Guidance
{
    private:
        Navigation *_nav;

        float _roll_d;
        float _pitch_d;
        float _yaw_d;
        float _T_d;

        float _k_xy, _k_vxy;
        float _gravity_guess;
        float _xi_g;


    public:
        Guidance();
        Guidance(Navigation *);
        ~Guidance();

        float get_roll_d();
        float get_pitch_d();
        float get_yaw_d();
        float get_T_d();

        void set_xyz_ned_lya(float *);

        void update(float);
};

#endif
