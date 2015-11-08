#ifndef XPTHROTLEC_HH
#define XPTHROTLEC_HH 1

#include <vector>
#include <iostream>
#include <string>

#include "XPdata.hh"

class XPthrottelc: public XPdata{
    private:
        float _t1c;
        float _t2c;
        float _t3c;
        float _t4c;
        float _t5c;
        float _t6c;
        float _t7c;
        float _t8c;

    public:
        XPthrottelc();
        XPthrottelc (std::vector<char>::iterator &) ;
        ~XPthrottelc();

        float get_t1c();
        float get_t2c();
        float get_t3c();
        float get_t4c();
        float get_t5c();
        float get_t6c();
        float get_t7c();
        float get_t8c();

        virtual void to_dtg(std::vector<char> &) const;
        virtual void accept(Sim *);
};

#endif
