#ifndef GUIDANCE_HH
#define GUIDANCE_HH 1

#include "sim.hh"
#include "navigation.hh"

class Guidance
{
    private:
        Sim *_sim;
        Navigation *_nav;

    public:
        Guidance();
        Guidance(Sim *, Navigation *);
        ~Guidance();

        void update();
};

#endif
