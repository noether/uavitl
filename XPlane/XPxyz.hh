#ifndef XPXYZ_HH
#define XPXYZ_HH 1

#include <vector>
#include <iostream>
#include <string>

#include "XPdata.hh"

class XPxyz: public XPdata{
    private:
        float _x;
        float _y;
        float _z;
        float _vx;
        float _vy;
        float _vz;
        float _dFt;
        float _dNm;

    public:
        XPxyz();
        XPxyz (std::vector<char>::iterator &i) ;
        ~XPxyz();

        float get_x();
        float get_y();
        float get_z();
        float get_vx();
        float get_vy();
        float get_vz();
        float get_dFt();
        float get_dNm();

        virtual void to_dtg(std::vector<char> &dtg) const;
};

#endif
