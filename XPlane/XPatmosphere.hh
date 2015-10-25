#ifndef XPATMOSPHERE_HH
#define XPATMOSPHERE_HH 1

#include <vector>
#include <iostream>
#include <string>

#include "XPdata.hh"

class XPatmosphere: public XPdata{
    private:
        float _AMpressure;
        float _AMtmp;
        float _LEtmp;
        float _rho;
        float _A;
        float _Q;
        float _g;

    public:
        XPatmosphere();
        XPatmosphere(std::vector<char>::iterator &i);
        ~XPatmosphere();

        float get_AMpressure();
        float get_AMtmp();
        float get_LEtmp();
        float get_rho();
        float get_A();
        float get_Q();
        float get_g();

        virtual void to_dtg(std::vector<char> &dtg) const;
};

#endif
