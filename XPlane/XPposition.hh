#ifndef XPPOSITION_HH
#define XPPOSITION_HH 1

#include <vector>
#include <iostream>
#include <string>

#include "XPdata.hh"

class XPposition: public XPdata{
    private:
        float _latitude;
        float _longitude;
        float _fmsl;
        float _fagl;
        float _onrw;
        float _altitudeIndic;
        float _latSouth;
        float _longWest;

    public:
        XPposition();
        XPposition (std::vector<char>::iterator &i) ;
        ~XPposition();

        float get_latitude();
        float get_longitude();
        float get_altitudeFmsl();
        float get_altitudeFagl();
        float get_onrw();
        float get_altitudeIndic();
        float get_latitudeS();
        float get_longitudeW();

        virtual std::ostream& oo(std::ostream& o) const;
        virtual void to_dtg(std::vector<char> &dtg) const;
};

#endif
