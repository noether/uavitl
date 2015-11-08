#include "gnc.hh"

GNC::GNC(Guidance *g, Navigation *n, Control *c):
    _g(g),
    _n(n),
    _c(c)
{
}

GNC::GNC()
{
}

GNC::~GNC()
{
}

void GNC::set_guidance(Guidance *g)
{
    _g = g;
}

void GNC::set_navigation(Navigation *n)
{
    _n = n;
}

void GNC::set_control(Control *c)
{
    _c = c;
}

Navigation * GNC::get_nav()
{
    return _n;
}
