#include <vector>
#include <ostream>

#include "XPgps.hh"

XPgps::XPgps():
    _latitude(-999),
    _longitude(-999),
    _fmsl(-999),
    _fagl(-999),
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

std::ostream& XPgps::oo (std::ostream& o)  const{
    return o << "Latitude: " << this->_latitude << " degrees" << std::endl
        << "Longitude: " << this->_longitude << " degrees" << std::endl 
        << "Altitude: " << this->_fmsl << " fmsl" << std::endl
        << "Altitude: " << this->_fagl << " fagl" << std::endl
        << "Altitude indicated: " << this->_altitudeIndic << std::endl
        << "Latitude South: " << this->_latSouth << std::endl
        << "Longitude West: " << this->_longWest << std::endl;
}

void XPgps::to_dtg(std::vector<char> &dtg) const{
    int long_dtg= dtg.size();
    int index= 20;

    dtg.resize(long_dtg+36);
    std::vector<char>::iterator i(dtg.begin()+long_dtg);

    insert_in_dtg(i, index);
    insert_in_dtg(i, _latitude);
    insert_in_dtg(i, _longitude);
    insert_in_dtg(i, _fmsl);
    insert_in_dtg(i, _fagl);
    insert_in_dtg(i, _altitudeIndic);
    insert_in_dtg(i, _latSouth);
    insert_in_dtg(i, _longWest);
}
