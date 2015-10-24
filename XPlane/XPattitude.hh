#ifndef XPATTIUDE_HH
#define XPATTIUDE_HH 1

#include <vector>
#include <iostream>
#include <string>

#include "XPdata.hh"

class XPattitude: public XPdata{
    private:
        float _pitch;
        float _roll;
        float _yaw;
        float _magneticHeading;
        float _magVar;

    public:
        XPattitude();
        XPattitude(std::vector<char>::iterator &i);
        ~XPattitude();

        float get_pitch();
        float get_roll();
        float get_yaw();
        float get_magneticHeading();
        float get_magVar();

        virtual std::ostream& oo(std::ostream& o) const;
        virtual void to_dtg(std::vector<char> &dtg) const;
};

#endif
