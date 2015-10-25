#ifndef XPLOADS_HH
#define XPLOADS_HH 1

#include <vector>
#include <iostream>
#include <string>

#include "XPdata.hh"

class XPloads: public XPdata{
    private:
        float _mach;
        float _vvi;
        float _gNormal;
        float _gAxial;
        float _gSide;

    public:
        XPloads();
        XPloads (std::vector<char>::iterator &i) ;
        ~XPloads();

        float get_mach();
        float get_vvi();
        float get_gNormal();
        float get_gAxial();
        float get_gSide();

        virtual void to_dtg(std::vector<char> &dtg) const;
};

#endif
