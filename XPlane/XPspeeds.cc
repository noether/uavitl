#include <vector>
#include <ostream>

#include "XPdata.hh"
#include "XPspeeds.hh"

XPspeeds::XPspeeds():
    _vindKias(-999),
    _vindKeas(-999),
    _vtrueKtas(-999),
    _vtrueKtgs(-999),
    _vindMph(-999),
    _vtrueMphas(-999),
    _vtrueMphgs(-999)
{
}

XPspeeds::XPspeeds(std::vector<char>::iterator & i){
    _vindKias = *reinterpret_cast<float*>(&*(i));
    _vindKeas = *reinterpret_cast<float*>(&*(i+=4));
    _vtrueKtas = *reinterpret_cast<float*>(&*(i+=4));
    _vtrueKtgs = *reinterpret_cast<float*> (&*(i+=4));
    _vindMph = *reinterpret_cast<float*> (&*(i+=8));
    _vtrueMphas = *reinterpret_cast<float*> (&*(i+=4));
    _vtrueMphgs = *reinterpret_cast<float*> (&*(i+=4));

    i += 4;
}

XPspeeds::~XPspeeds(){
}


float XPspeeds::get_vindKias(){
    return _vindKias;
}

float XPspeeds::get_vindKeas(){
    return _vindKeas;
}

float XPspeeds::get_vtrueKtas(){
    return _vtrueKtas;
}

float XPspeeds::get_vtrueKtgs(){
    return _vtrueKtgs;
}

float XPspeeds::get_vindMph(){
    return _vindMph;
}

float XPspeeds::get_vtrueMphas(){
    return _vtrueMphas;
}

float XPspeeds::get_vtrueMphgs(){
    return _vtrueMphgs;
}

void XPspeeds::to_dtg(std::vector<char> &dtg) const{
    int long_dtg = dtg.size();
    int index = XPID_SPEEDS;

    dtg.resize(long_dtg + 36);
    std::vector<char>::iterator i(dtg.begin()+long_dtg);

    insert_in_dtg(i, index);
    insert_in_dtg(i, _vindKias);
    insert_in_dtg(i, _vindKeas);
    insert_in_dtg(i, _vtrueKtas);
    insert_in_dtg(i, _vtrueKtgs);
    insert_in_dtg(i, -999);
    insert_in_dtg(i, _vindMph);
    insert_in_dtg(i, _vtrueMphas);
    insert_in_dtg(i, _vtrueMphgs);
}
