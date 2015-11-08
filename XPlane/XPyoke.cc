#include <vector>
#include <ostream>

#include "XPdata.hh"
#include "XPyoke.hh"
#include "../sim.hh"

XPyoke::XPyoke():
    _elev(-999),
    _ail(-999),
    _rud(-999)
{
}

XPyoke::XPyoke(std::vector<char>::iterator & i){
    _elev = *reinterpret_cast<float*>(&*(i));
    _ail = *reinterpret_cast<float*>(&*(i+=4));
    _rud = *reinterpret_cast<float*>(&*(i+=4));

    i += 24;
}

XPyoke::~XPyoke(){
}


float XPyoke::get_elev(){
    return _elev;
}


float XPyoke::get_ail(){
    return _ail;
}


float XPyoke::get_rud(){
    return _rud;
}

void XPyoke::to_dtg(std::vector<char> &dtg) const{
    int long_dtg = dtg.size();
    int index = XPID_YOKE;

    dtg.resize(long_dtg + 36);
    std::vector<char>::iterator i(dtg.begin() + long_dtg);

    insert_in_dtg(i, index);
    insert_in_dtg(i, _elev);
    insert_in_dtg(i, _ail);
    insert_in_dtg(i, _rud);
    insert_in_dtg(i, -999);
    insert_in_dtg(i, -999);
    insert_in_dtg(i, -999);
    insert_in_dtg(i, -999);
    insert_in_dtg(i, -999);
}

void XPyoke::accept(Sim * s)
{
    s->visit(this);
}
