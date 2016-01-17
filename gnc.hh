#ifndef GNC_HH
#define GNC_HH 1

#include "sim.hh"

class GNC{
    protected:
        Sim *_sim;

    public:
        GNC(Sim *);
        GNC();
        ~GNC();

        virtual void update(long) =0;
};

#endif
