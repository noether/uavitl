#include <vector>
#include <ostream>

#include "XPdata.hh"
#include "XPloads.hh"
#include "../sim.hh"

XPloads::XPloads():
    _mach(-999),
    _vvi(-999),
    _gNormal(-999),
    _gAxial(-999),
    _gSide(-999)
{
}

XPloads::XPloads(std::vector<char>::iterator & i){
    _mach = *reinterpret_cast<float*>(&*(i));
    _vvi = *reinterpret_cast<float*>(&*(i+=8)); 
    _gNormal = *reinterpret_cast<float*> (&*(i+=8));
    _gAxial = *reinterpret_cast<float*> (&*(i+=4));
    _gSide = *reinterpret_cast<float*> (&*(i+=4));

    i += 8;
}

XPloads::~XPloads(){
}


float XPloads::get_mach(){
    return _mach;
}

float XPloads::get_vvi(){
    return _vvi;
}


float XPloads::get_gNormal(){
    return _gNormal;
}

float XPloads::get_gAxial(){
    return _gAxial;
}

float XPloads::get_gSide(){
    return _gSide;
}

void XPloads::to_dtg(std::vector<char> &dtg) const{
    int long_dtg = dtg.size();
    int index = XPID_LOADS;

    dtg.resize(long_dtg + 36);
    std::vector<char>::iterator i(dtg.begin()+long_dtg);

    insert_in_dtg(i, index);
    insert_in_dtg(i, _mach);
    insert_in_dtg(i, -999);
    insert_in_dtg(i, _vvi);
    insert_in_dtg(i, -999);
    insert_in_dtg(i, _gNormal);
    insert_in_dtg(i, _gAxial);
    insert_in_dtg(i, _gSide);
    insert_in_dtg(i, -999);
}

void XPloads::accept(Sim * s)
{
    s->visit(this);
}
