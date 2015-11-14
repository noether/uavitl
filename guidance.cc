#include "guidance.hh"

Guidance::Guidance():
    _sim(NULL),
    _nav(NULL)
{
}

Guidance::Guidance(Sim *s, Navigation *n):
    _sim(s),
    _nav(n)
{
}

Guidance::~Guidance()
{
}

void Guidance::update()
{

}
