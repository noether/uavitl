#ifndef GNC_HH
#define GNC_HH 1

#include "guidance.hh"
#include "navigation.hh"
#include "control.hh"

class GNC{
    private:
        Guidance *_g;
        Navigation *_n;
        Control *_c;

    public:
        GNC(Guidance*, Navigation*, Control*);
        GNC();
        ~GNC();

        void set_guidance(Guidance*);
        void set_navigation(Navigation*);
        void set_control(Control*);

        Navigation * get_nav();
};

#endif
