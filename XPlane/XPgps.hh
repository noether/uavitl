#ifndef XPGPS_HH
#define XPGPS_HH 1

#include <vector>
#include <iostream>
#include <string>

#include "XPdata.hh"

class XPgps: public XPdata{
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
        XPgps();
        XPgps (std::vector<char>::iterator &);
        ~XPgps();

        float get_latitude();
        float get_longitude();
        float get_altitudeFmsl();
        float get_altitudeFagl();
        float get_onrw();
        float get_altitudeIndic();
        float get_latitudeS();
        float get_longitudeW();

        virtual void to_dtg(std::vector<char> &) const;
        virtual void accept(Sim *);
};

#endif
