#ifndef GUIDANCE_HH
#define GUIDANCE_HH 1

#include "sim.hh"
#include "navigation.hh"

class Guidance
{
    private:
        Navigation *_nav;

        float _m;
        float _aE;
        float _aN;
        float _aU;

        float _e_amsl;
        float _e_psi;
        float _e_phi;
        float _e_the;

        float _e_az;

    public:
        Guidance();
        Guidance(Navigation *);
        ~Guidance();

        float get_e_amsl();
        float get_e_psi();
        float get_e_phi();
        float get_e_the();
        float get_e_az();

        void update();
};

#endif
