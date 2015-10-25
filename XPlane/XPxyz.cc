#include <vector>
#include <ostream>

#include "XPdata.hh"
#include "XPxyz.hh"

XPxyz::XPxyz():
    _x(-999),
    _y(-999),
    _z(-999),
    _vx(-999),
    _vy(-999),
    _vz(-999),
    _dFt(-999),
    _dNm(-999)
{
}

XPxyz::XPxyz(std::vector<char>::iterator & i){
    _x = *reinterpret_cast<float*>(&*(i));
    _y = *reinterpret_cast<float*>(&*(i+=4));
    _z = *reinterpret_cast<float*>(&*(i+=4)); 
    _vx = *reinterpret_cast<float*> (&*(i+=4));
    _vy = *reinterpret_cast<float*> (&*(i+=4));
    _vz = *reinterpret_cast<float*> (&*(i+=4));
    _dFt = *reinterpret_cast<float*> (&*(i+=4));
    _dNm = *reinterpret_cast<float*> (&*(i+=4));

    i += 4;
}

XPxyz::~XPxyz(){
}

float XPxyz::get_x(){
    return _x;
}

float XPxyz::get_y(){
    return _y;
}

float XPxyz::get_z(){
    return _z;
}

float XPxyz::get_vx(){
    return _vx;
}

float XPxyz::get_vy(){
    return _vy;
}

float XPxyz::get_vz(){
    return _vz;
}

float XPxyz::get_dFt(){
    return _dFt;
}

float XPxyz::get_dNm(){
    return _dNm;
}

void XPxyz::to_dtg(std::vector<char> &dtg) const{
    int long_dtg = dtg.size();
    int index = XPID_GPS;

    dtg.resize(long_dtg + 36);
    std::vector<char>::iterator i(dtg.begin()+long_dtg);

    insert_in_dtg(i, index);
    insert_in_dtg(i, _x);
    insert_in_dtg(i, _y);
    insert_in_dtg(i, _z);
    insert_in_dtg(i, _vx);
    insert_in_dtg(i, _vy);
    insert_in_dtg(i, _vz);
    insert_in_dtg(i, _dFt);
    insert_in_dtg(i, _dNm);
}
