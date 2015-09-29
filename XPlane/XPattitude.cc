#include <vector>
#include <ostream>

#include "XPattitude.hh"

XPattitude::XPattitude():
    _pitch(-999),
    _roll(-999),
    _yaw(-999),
    _magneticHeading(-999),
    _magVar(-999),
    _headingBug(-999)
{
}

XPattitude::XPattitude(std::vector<char>::iterator & i){
    float unknown;

    _pitch= *reinterpret_cast<float*>(&*(i));
    _roll= *reinterpret_cast<float*>(&*(i+4));
    _yaw = *reinterpret_cast<float*>(&*(i+8)); 
    _magneticHeading = *reinterpret_cast<float*> (&*(i+12));
    _magVar = *reinterpret_cast<float*> (&*(i+16));
    _headingBug = *reinterpret_cast<float*> (&*(i+20));
    unknown = *reinterpret_cast<float*> (&*(i+24));
    unknown = *reinterpret_cast<float*> (&*(i+28));
    i += 4;

    unknown = unknown; // Keep compiler quiet
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

float XPattitude::get_headingBug(){
    return _headingBug;
}

std::ostream& XPattitude::oo (std::ostream& o)  const{
    return o << "Pitch: " << this->_pitch << " degrees" << std::endl
        << "Roll: " << this->_roll << " degrees" << std::endl
        << "Yaw: " << this->_yaw << " degrees" << std::endl
        << "Magnetic Heading: " << this->_magneticHeading << " degrees"
        << std::endl
        << "Mag Var: " << this->_magVar << " degrees" << std::endl
        << "Heading bug: " << this->_headingBug << " degrees" << std::endl;
}

void XPattitude::to_dtg(std::vector<char> &dtg) const{
    int long_dtg= dtg.size();
    int index= 18;

    dtg.resize(long_dtg+36);
    std::vector<char>::iterator i(dtg.begin()+long_dtg);

    insert_in_dtg(i, index);
    insert_in_dtg(i, _pitch);
    insert_in_dtg(i, _roll);
    insert_in_dtg(i, _yaw);
    insert_in_dtg(i, _magneticHeading);
    insert_in_dtg(i, _magVar);
    insert_in_dtg(i, _headingBug);
}
