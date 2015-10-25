#include "XPdata.hh"
#include "XPattitude.hh"
#include "XPatmosphere.hh"
#include "XPgps.hh"
#include "XPaerangles.hh"
#include "XPpqr.hh"
#include "XPspeeds.hh"

#include <iostream>

XPdata::XPdata(){
}

XPdata::~XPdata(){
}

XPdata* XPdata::create(std::vector<char>::iterator &i) {
    switch (*i) {
        case XPID_SPEEDS:
            i+=4;
            return new XPspeeds(i);

        case XPID_ATM_PLANE:
            i+=4;
            return new XPatmosphere(i);

        case XPID_PQR:
            i+=4;
            return new XPpqr(i);

        case XPID_AER_ANGLES:
            i+=4;
            return new XPaerangles(i);

        case XPID_ATTITUDE:
            i+=4;
            return new XPattitude(i);
            break;

        case XPID_GPS:
            i+=4;
            return new XPgps(i);
            break;

        default:
            i+=36;
            return 0;
            break;
    }
}

void XPdata::prologue_to_dtg(std::vector<char> &dtg) {
    int long_dtg = dtg.size();
    dtg.resize(long_dtg + 5);

    std::vector<char>::iterator i(dtg.begin()+long_dtg);

    insert_in_dtg(i, 'D');
    insert_in_dtg(i, 'A');
    insert_in_dtg(i, 'T');
    insert_in_dtg(i, 'A');
    insert_in_dtg(i, 0x00);
}
