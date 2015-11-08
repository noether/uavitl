#include <vector>
#include <ostream>

#include "XPdata.hh"
#include "XPgearbrakes.hh"
#include "../sim.hh"

XPgearbrakes::XPgearbrakes():
    _gear(-999),
    _bw(-999),
    _bl(-999),
    _br(-999)
{
}

XPgearbrakes::XPgearbrakes(std::vector<char>::iterator & i){
    _gear = *reinterpret_cast<float*>(&*(i));
    _bw = *reinterpret_cast<float*>(&*(i+=4));
    _bl = *reinterpret_cast<float*>(&*(i+=4));
    _br = *reinterpret_cast<float*> (&*(i+=4));

    i += 24;
}

XPgearbrakes::~XPgearbrakes(){
}


float XPgearbrakes::get_gear(){
    return _gear;
}

float XPgearbrakes::get_bw(){
    return _bw;
}

float XPgearbrakes::get_bl(){
    return _bl;
}

float XPgearbrakes::get_br(){
    return _br;
}

void XPgearbrakes::to_dtg(std::vector<char> &dtg) const{
    int long_dtg = dtg.size();
    int index = XPID_GEAR_BRAKES;

    dtg.resize(long_dtg + 36);
    std::vector<char>::iterator i(dtg.begin()+long_dtg);

    insert_in_dtg(i, index);
    insert_in_dtg(i, _gear);
    insert_in_dtg(i, _bw);
    insert_in_dtg(i, _bl);
    insert_in_dtg(i, _br);
    insert_in_dtg(i, -999);
    insert_in_dtg(i, -999);
    insert_in_dtg(i, -999);
    insert_in_dtg(i, -999);
}

void XPgearbrakes::accept(Sim * s)
{
    s->visit(this);
}
