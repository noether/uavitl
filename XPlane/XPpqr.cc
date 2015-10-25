#include <vector>
#include <ostream>

#include "XPdata.hh"
#include "XPpqr.hh"

XPpqr::XPpqr():
    _p(-999),
    _q(-999),
    _r(-999)
{
}

XPpqr::XPpqr(std::vector<char>::iterator & i){
    _p = *reinterpret_cast<float*>(&*(i));
    _q = *reinterpret_cast<float*>(&*(i+=4));
    _r = *reinterpret_cast<float*>(&*(i+=4));
    i += 24;
}

XPpqr::~XPpqr(){
}


float XPpqr::get_p(){
    return _p;
}


float XPpqr::get_q(){
    return _q;
}


float XPpqr::get_r(){
    return _r;
}

void XPpqr::to_dtg(std::vector<char> &dtg) const{
    int long_dtg = dtg.size();
    int index = XPID_PQR;

    dtg.resize(long_dtg + 36);
    std::vector<char>::iterator i(dtg.begin() + long_dtg);

    insert_in_dtg(i, index);
    insert_in_dtg(i, _p);
    insert_in_dtg(i, _q);
    insert_in_dtg(i, _r);
    insert_in_dtg(i, -999);
    insert_in_dtg(i, -999);
    insert_in_dtg(i, -999);
    insert_in_dtg(i, -999);
    insert_in_dtg(i, -999);
}
