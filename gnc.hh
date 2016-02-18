#ifndef GNC_HH
#define GNC_HH 1

#include "sim.hh"

class GNC{
    protected:
        int _id;
        Sim *_sim;

    public:
        GNC(int, Sim *);
        GNC();
        ~GNC();

        virtual void update(long) =0;
};

#endif
