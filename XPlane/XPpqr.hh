#ifndef XPPQR_HH
#define XPPQR_HH 1

#include <vector>
#include <iostream>
#include <string>

#include "XPdata.hh"

class XPpqr: public XPdata{
    private:
        float _p;
        float _q;
        float _r;

    public:
        XPpqr();
        XPpqr(std::vector<char>::iterator &i);
        ~XPpqr();

        float get_p();
        float get_q();
        float get_r();

        virtual void to_dtg(std::vector<char> &dtg) const;
};

#endif
