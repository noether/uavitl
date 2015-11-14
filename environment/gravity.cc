#include <math.h>

#include "gravity.hh"

Gravity::Gravity():
	_GMe(3986000.9e8),          // Atmosphere Not Included [m³/s²]
	_MassEarth(5.9733328e24),   // Mass of Earth [kg]
	_G(6.673e-11),              // Gravitational Constant [m³/kg s²]
	_a(6378137),                // Equatorial radius [m]
	_b(6356752.3142),           // Polar radius [m]
	_ge(9.7803253359),          // Theoretical gravity at the equator[m/s²]
	_gp(9.8321849378),          // Theoretical gravity at the pole [m/s²]
	_e2(6.69437999014e-3),      // square of the first ellipsoidal eccentricity
	_m(0.00344978650684),       // derived constant
	_f(1/298.257223563),        // flattening
	_k(0.00193185265241)        // Theoretical Gravity Formula Constant
{
}

Gravity::~Gravity()
{
}

float Gravity::g(float phi_geodetic, float altitude)
{
	float g_surface = _ge * (1 + _k*sinf(phi_geodetic)*sinf(phi_geodetic)) /
		(sqrtf(1 - _e2*sinf(phi_geodetic)*sinf(phi_geodetic)));

	float g = g_surface * (1 - 2/_a*(1 + _f + _m -
		2*_f*sinf(phi_geodetic)*sinf(phi_geodetic))*altitude +
		3/(_a*_a)*altitude*altitude);

	return g;
}
