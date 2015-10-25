#ifndef XPTHROTLEA_HH
#define XPTHROTLEA_HH 1

#include <vector>
#include <iostream>
#include <string>

#include "XPdata.hh"

class XPthrottela: public XPdata{
    private:
        float _t1a;
        float _t2a;
        float _t3a;
        float _t4a;
        float _t5a;
        float _t6a;
        float _t7a;
        float _t8a;

    public:
        XPthrottela();
        XPthrottela (std::vector<char>::iterator &i) ;
        ~XPthrottela();

        float get_t1a();
        float get_t2a();
        float get_t3a();
        float get_t4a();
        float get_t5a();
        float get_t6a();
        float get_t7a();
        float get_t8a();

        virtual void to_dtg(std::vector<char> &dtg) const;
};

#endif
