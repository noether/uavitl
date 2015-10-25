#include <vector>
#include <ostream>

#include "XPdata.hh"
#include "XPthrottela.hh"

XPthrottela::XPthrottela():
    _t1a(-999),
    _t2a(-999),
    _t3a(-999),
    _t4a(-999),
    _t5a(-999),
    _t6a(-999),
    _t7a(-999),
    _t8a(-999)
{
}

XPthrottela::XPthrottela(std::vector<char>::iterator & i){
    _t1a = *reinterpret_cast<float*>(&*(i));
    _t2a = *reinterpret_cast<float*>(&*(i+=4));
    _t3a = *reinterpret_cast<float*>(&*(i+=4));
    _t4a = *reinterpret_cast<float*>(&*(i+=4));
    _t5a = *reinterpret_cast<float*>(&*(i+=4));
    _t6a = *reinterpret_cast<float*>(&*(i+=4));
    _t7a = *reinterpret_cast<float*>(&*(i+=4));
    _t8a = *reinterpret_cast<float*>(&*(i+=4));

    i += 4;
}

XPthrottela::~XPthrottela(){
}

float XPthrottela::get_t1a(){
    return _t1a;
}

float XPthrottela::get_t2a(){
    return _t2a;
}

float XPthrottela::get_t3a(){
    return _t3a;
}

float XPthrottela::get_t4a(){
    return _t4a;
}

float XPthrottela::get_t5a(){
    return _t5a;
}

float XPthrottela::get_t6a(){
    return _t6a;
}

float XPthrottela::get_t7a(){
    return _t7a;
}

float XPthrottela::get_t8a(){
    return _t8a;
}

void XPthrottela::to_dtg(std::vector<char> &dtg) const{
    int long_dtg = dtg.size();
    int index = XPID_THROTTEL_A;

    dtg.resize(long_dtg + 36);
    std::vector<char>::iterator i(dtg.begin()+long_dtg);

    insert_in_dtg(i, index);
    insert_in_dtg(i, _t1a);
    insert_in_dtg(i, _t2a);
    insert_in_dtg(i, _t3a);
    insert_in_dtg(i, _t4a);
    insert_in_dtg(i, _t5a);
    insert_in_dtg(i, _t6a);
    insert_in_dtg(i, _t7a);
    insert_in_dtg(i, _t8a);
}
