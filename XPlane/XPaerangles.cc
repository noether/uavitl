#include <vector>
#include <ostream>

#include "XPdata.hh"
#include "XPaerangles.hh"

XPaerangles::XPaerangles():
    _aoa(-999),
    _aos(-999),
    _hpath(-999),
    _vpath(-999),
    _slip(-999)
{
}

XPaerangles::XPaerangles(std::vector<char>::iterator & i){
    _aoa = *reinterpret_cast<float*>(&*(i));
    _aos = *reinterpret_cast<float*>(&*(i+=4));
    _hpath = *reinterpret_cast<float*>(&*(i+=4));
    _vpath = *reinterpret_cast<float*> (&*(i+=4));
    _slip = *reinterpret_cast<float*> (&*(i+=16));
    i += 4;
}

XPaerangles::~XPaerangles(){
}


float XPaerangles::get_aoa(){
    return _aoa;
}

float XPaerangles::get_aos(){
    return _aos;
}

float XPaerangles::get_hpath(){
    return _hpath;
}

float XPaerangles::get_vpath(){
    return _vpath;
}

float XPaerangles::get_slip(){
    return _slip;
}

void XPaerangles::to_dtg(std::vector<char> &dtg) const{
    int long_dtg = dtg.size();
    int index = XPID_AER_ANGLES;

    dtg.resize(long_dtg + 36);
    std::vector<char>::iterator i(dtg.begin() + long_dtg);

    insert_in_dtg(i, index);
    insert_in_dtg(i, _aoa);
    insert_in_dtg(i, _aos);
    insert_in_dtg(i, _hpath);
    insert_in_dtg(i, _vpath);
    insert_in_dtg(i, -999);
    insert_in_dtg(i, -999);
    insert_in_dtg(i, -999);
    insert_in_dtg(i, _slip);
}
