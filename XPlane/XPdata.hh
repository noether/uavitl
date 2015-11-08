#ifndef XPLANEDATA_HH
#define XPLANEDATA_HH 1

#include <tr1/memory>
#include <iostream>
#include <vector>
#include <string.h>

enum XP_ID{
  XPID_SPEEDS = 3,
  XPID_LOADS = 4,
  XPID_ATM_PLANE = 6,
  XPID_YOKE = 8,
  XPID_GEAR_BRAKES = 14,
  XPID_PQR = 17,
  XPID_ATTITUDE = 18,
  XPID_AER_ANGLES = 19,
  XPID_GPS = 20,
  XPID_XYZ = 21,
  XPID_THROTTEL_C = 25,
  XPID_THROTTEL_A = 26
};


template <typename T> void insert_in_dtg(std::vector<char>::iterator & i, T t) {
    memcpy(&*i, &t, sizeof(t));
    i += sizeof(t);
};

class Sim;

class XPdata{
    public:
        XPdata();
        ~XPdata();

        static XPdata* create(std::vector<char>::iterator &);
        static void prologue_to_dtg(std::vector<char> &);

        virtual void to_dtg(std::vector<char> &) const = 0;
        virtual void accept(Sim *) = 0;
};

typedef std::vector<std::tr1::shared_ptr<XPdata> > XPdataVector;

#endif
