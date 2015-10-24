#include "XPdata.hh"
#include "XPattitude.hh"
#include "XPgps.hh"

#include <iostream>

XPdata::XPdata(){
}

XPdata::~XPdata(){
}

std::ostream& operator<<(std::ostream &o, const XPdata &d) {
    return d.oo(o);
}

XPdata* XPdata::create(std::vector<char>::iterator &i) {
    switch (*i) {
        case 18:
            std::cout << "Attitude recieved!" << std::endl;
            i+=4; // ID is codified with 4 bytes
            return new XPattitude(i); // Data Payload
            break;

        case 20:
            std::cout << "GPS recieved!" << std::endl;
            i+=4;
            return new XPgps(i);
            break;

        default:
            i+=36;
            return 0; // TODO
            break;
    }
}

void XPdata::prologue_to_dtg(std::vector<char> &dtg) {
    int long_dtg = dtg.size();
    dtg.resize(long_dtg+5);

    std::vector<char>::iterator i(dtg.begin()+long_dtg);

    insert_in_dtg(i, 'D');
    insert_in_dtg(i, 'A');
    insert_in_dtg(i, 'T');
    insert_in_dtg(i, 'A');
    insert_in_dtg(i, 0x00);
}
