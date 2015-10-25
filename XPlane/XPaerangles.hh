#ifndef XPAERANGLES_HH
#define XPAERANGLES_HH 1

#include <vector>
#include <iostream>
#include <string>

#include "XPdata.hh"

class XPaerangles: public XPdata{
    private:
        float _aoa;
        float _aos;
        float _hpath;
        float _vpath;
        float _slip;

    public:
        XPaerangles();
        XPaerangles(std::vector<char>::iterator &i);
        ~XPaerangles();

        float get_aoa();
        float get_aos();
        float get_hpath();
        float get_vpath();
        float get_slip();

        virtual void to_dtg(std::vector<char> &dtg) const;
};

#endif
