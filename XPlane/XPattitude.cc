#include <vector>
#include <ostream>

#include "XPattitude.hh"

XPattitude::XPattitude():
    _pitch(-999),
    _roll(-999),
    _yaw(-999),
    _magneticHeading(-999),
    _magVar(-999)
{
}

XPattitude::XPattitude(std::vector<char>::iterator & i){
    _pitch= *reinterpret_cast<float*>(&*(i));
    _roll= *reinterpret_cast<float*>(&*(i+=4));
    _yaw = *reinterpret_cast<float*>(&*(i+=4));
    _magneticHeading = *reinterpret_cast<float*> (&*(i+=4));
    _magVar = *reinterpret_cast<float*> (&*(i+=16));
    i += 4;
}

XPattitude::~XPattitude(){
}


float XPattitude::get_pitch(){
    return _pitch;
}


float XPattitude::get_roll(){
    return _roll;
}


float XPattitude::get_yaw(){
    return _yaw;
}


float XPattitude::get_magneticHeading(){
    return _magneticHeading;
}

float XPattitude::get_magVar(){
    return _magVar;
}

void XPattitude::to_dtg(std::vector<char> &dtg) const{
    int long_dtg = dtg.size();
    int index = 18;

    dtg.resize(long_dtg + 36);
    std::vector<char>::iterator i(dtg.begin() + long_dtg);

    insert_in_dtg(i, index);
    insert_in_dtg(i, _pitch);
    insert_in_dtg(i, _roll);
    insert_in_dtg(i, _yaw);
    insert_in_dtg(i, _magneticHeading);
    insert_in_dtg(i, _magVar);
}
