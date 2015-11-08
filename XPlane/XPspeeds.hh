#ifndef XPSPEEDS_HH
#define XPSPEEDS_HH 1

#include <vector>
#include <iostream>
#include <string>

#include "XPdata.hh"

class XPspeeds: public XPdata{
    private:
        float _vindKias;
        float _vindKeas;
        float _vtrueKtas;
        float _vtrueKtgs;
        float _vindMph;
        float _vtrueMphas;
        float _vtrueMphgs;

    public:
        XPspeeds();
        XPspeeds (std::vector<char>::iterator &) ;
        ~XPspeeds();

        float get_vindKias();
        float get_vindKeas();
        float get_vtrueKtas();
        float get_vtrueKtgs();
        float get_vindMph();
        float get_vtrueMphas();
        float get_vtrueMphgs();

        virtual void to_dtg(std::vector<char> &) const;
        virtual void accept(Sim *);
};

#endif
