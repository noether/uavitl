#ifndef XPLANEDATA_HH
#define XPLANEDATA_HH 1

#include <tr1/memory>
#include <iostream>
#include <vector>
#include <string.h>

template <typename T> void insert_in_dtg(std::vector<char>::iterator & i, T t) {
    memcpy(&*i, &t, sizeof(t));
    i += sizeof(t);
};

class XPdata{
    public:
        XPdata();
        ~XPdata();

        virtual std::ostream& oo(std::ostream &f) const=0;
        friend std::ostream& operator<<(std::ostream &o, const XPdata &d);

        static XPdata* create(std::vector<char>::iterator& i);
        static void prologue_to_dtg(std::vector<char> &dtg);

        virtual void to_dtg(std::vector<char> &dtg) const=0;
};

typedef std::vector<std::tr1::shared_ptr<XPdata> > XPdataVector;

#endif
