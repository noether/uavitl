#ifndef XPGEARBRAKES_HH
#define XPGEARBRAKES_HH 1

#include <vector>
#include <iostream>
#include <string>

#include "XPdata.hh"

class XPgearbrakes: public XPdata{
    private:
        float _gear;
        float _bw;
        float _bl;
        float _br;

    public:
        XPgearbrakes();
        XPgearbrakes (std::vector<char>::iterator &) ;
        ~XPgearbrakes();

        float get_gear();
        float get_bw();
        float get_bl();
        float get_br();

        virtual void to_dtg(std::vector<char> &) const;
        virtual void accept(Sim *);
};

#endif
