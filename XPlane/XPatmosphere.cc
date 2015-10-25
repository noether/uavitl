#include <vector>
#include <ostream>

#include "XPatmosphere.hh"

XPatmosphere::XPatmosphere():
    _AMpressure(-999),
    _AMtmp(-999),
    _LEtmp(-999),
    _rho(-999),
    _A(-999),
    _Q(-999),
    _g(-999)
{
}

XPatmosphere::XPatmosphere(std::vector<char>::iterator & i){
    _AMpressure = *reinterpret_cast<float*>(&*(i));
    _AMtmp = *reinterpret_cast<float*>(&*(i+=4));
    _LEtmp = *reinterpret_cast<float*>(&*(i+=4));
    _rho = *reinterpret_cast<float*> (&*(i+=4));
    _A = *reinterpret_cast<float*> (&*(i+=4));
    _Q = *reinterpret_cast<float*> (&*(i+=4));
    _g = *reinterpret_cast<float*> (&*(i+=8));
    i += 4;
}

XPatmosphere::~XPatmosphere(){
}


float XPatmosphere::get_AMpressure(){
    return _AMpressure;
}


float XPatmosphere::get_AMtmp(){
    return _AMtmp;
}

float XPatmosphere::get_LEtmp(){
    return _AMtmp;
}

float XPatmosphere::get_rho(){
    return _rho;
}

float XPatmosphere::get_A(){
    return _A;
}

float XPatmosphere::get_Q(){
    return _Q;
}

float XPatmosphere::get_g(){
    return _g;
}

void XPatmosphere::to_dtg(std::vector<char> &dtg) const{
    int long_dtg = dtg.size();
    int index = 6;

    dtg.resize(long_dtg + 36);
    std::vector<char>::iterator i(dtg.begin() + long_dtg);

    insert_in_dtg(i, index);
    insert_in_dtg(i, _AMpressure);
    insert_in_dtg(i, _AMtmp);
    insert_in_dtg(i, _LEtmp);
    insert_in_dtg(i, _rho);
    insert_in_dtg(i, _A);
    insert_in_dtg(i, _Q);
    insert_in_dtg(i, -999);
    insert_in_dtg(i, _g);
}
