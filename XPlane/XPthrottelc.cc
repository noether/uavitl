#include <vector>
#include <ostream>

#include "XPdata.hh"
#include "XPthrottelc.hh"
#include "../sim.hh"

XPthrottelc::XPthrottelc():
    _t1c(-999),
    _t2c(-999),
    _t3c(-999),
    _t4c(-999),
    _t5c(-999),
    _t6c(-999),
    _t7c(-999),
    _t8c(-999)
{
}

XPthrottelc::XPthrottelc(std::vector<char>::iterator & i){
    _t1c = *reinterpret_cast<float*>(&*(i));
    _t2c = *reinterpret_cast<float*>(&*(i+=4));
    _t3c = *reinterpret_cast<float*>(&*(i+=4));
    _t4c = *reinterpret_cast<float*>(&*(i+=4));
    _t5c = *reinterpret_cast<float*>(&*(i+=4));
    _t6c = *reinterpret_cast<float*>(&*(i+=4));
    _t7c = *reinterpret_cast<float*>(&*(i+=4));
    _t8c = *reinterpret_cast<float*>(&*(i+=4));

    i += 4;
}

XPthrottelc::XPthrottelc(float t1, float t2, float t3, float t4, 
        float t5, float t6, float t7, float t8)
{
    _t1c = t1;
    _t2c = t2;
    _t3c = t3;
    _t4c = t4;
    _t5c = t5;
    _t6c = t6;
    _t7c = t7;
    _t8c = t8;
}

XPthrottelc::~XPthrottelc(){
}

float XPthrottelc::get_t1c(){
    return _t1c;
}

float XPthrottelc::get_t2c(){
    return _t2c;
}

float XPthrottelc::get_t3c(){
    return _t3c;
}

float XPthrottelc::get_t4c(){
    return _t4c;
}

float XPthrottelc::get_t5c(){
    return _t5c;
}

float XPthrottelc::get_t6c(){
    return _t6c;
}

float XPthrottelc::get_t7c(){
    return _t7c;
}

float XPthrottelc::get_t8c(){
    return _t8c;
}

void XPthrottelc::to_dtg(std::vector<char> &dtg) const{
    int long_dtg = dtg.size();
    int index = XPID_THROTTEL_C;

    dtg.resize(long_dtg + 36);
    std::vector<char>::iterator i(dtg.begin()+long_dtg);

    insert_in_dtg(i, index);
    insert_in_dtg(i, _t1c);
    insert_in_dtg(i, _t2c);
    insert_in_dtg(i, _t3c);
    insert_in_dtg(i, _t4c);
    insert_in_dtg(i, _t5c);
    insert_in_dtg(i, _t6c);
    insert_in_dtg(i, _t7c);
    insert_in_dtg(i, _t8c);
}

void XPthrottelc::accept(Sim * s)
{
    s->visit(this);
}
