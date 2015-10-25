#ifndef XPYOKE_HH
#define XPYOKE_HH 1

#include <vector>
#include <iostream>
#include <string>

#include "XPdata.hh"

class XPyoke: public XPdata{
    private:
        float _elev;
        float _ail;
        float _rud;

    public:
        XPyoke();
        XPyoke (std::vector<char>::iterator &i) ;
        ~XPyoke();

        float get_elev();
        float get_ail();
        float get_rud();

        virtual void to_dtg(std::vector<char> &dtg) const;
};

#endif
