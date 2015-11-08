#include <vector>
#include <ostream>

#include "XPdata.hh"
#include "XPgps.hh"
#include "../sim.hh"

XPgps::XPgps():
    _latitude(-999),
    _longitude(-999),
    _fmsl(-999),
    _fagl(-999),
    _onrw(-999),
    _altitudeIndic(-999),
    _latSouth(-999),
    _longWest(-999)
{
}

XPgps::XPgps(std::vector<char>::iterator & i){
    _latitude = *reinterpret_cast<float*>(&*(i));
    _longitude = *reinterpret_cast<float*>(&*(i+=4));
    _fmsl = *reinterpret_cast<float*>(&*(i+=4)); 
    _fagl = *reinterpret_cast<float*> (&*(i+=4));
    _onrw = *reinterpret_cast<float*> (&*(i+=4));
    _altitudeIndic = *reinterpret_cast<float*> (&*(i+=4));
    _latSouth = *reinterpret_cast<float*> (&*(i+=4));
    _longWest = *reinterpret_cast<float*> (&*(i+=4));

    i += 4;
}

XPgps::~XPgps(){
}

float XPgps::get_latitude(){
    return _latitude;
}

float XPgps::get_longitude(){
    return _longitude;
}

float XPgps::get_altitudeFmsl(){
    return _fmsl;
}


float XPgps::get_altitudeFagl(){
    return _fagl;
}

float XPgps::get_onrw(){
    return _onrw;
}

float XPgps::get_altitudeIndic(){
    return _altitudeIndic;
}

float XPgps::get_latitudeS(){
    return _latSouth;
}

float XPgps::get_longitudeW(){
    return _longWest;
}

void XPgps::to_dtg(std::vector<char> &dtg) const{
    int long_dtg = dtg.size();
    int index = XPID_GPS;

    dtg.resize(long_dtg + 36);
    std::vector<char>::iterator i(dtg.begin()+long_dtg);

    insert_in_dtg(i, index);
    insert_in_dtg(i, _latitude);
    insert_in_dtg(i, _longitude);
    insert_in_dtg(i, _fmsl);
    insert_in_dtg(i, _fagl);
    insert_in_dtg(i, _onrw);
    insert_in_dtg(i, _altitudeIndic);
    insert_in_dtg(i, _latSouth);
    insert_in_dtg(i, _longWest);
}

void XPgps::accept(Sim * s)
{
    s->visit(this);
}
