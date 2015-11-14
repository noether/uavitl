// WGS84 gravity model

#ifndef GRAVITY_HH
#define GRAVITY_HH 1

class Gravity
{
	private:
		float _GMe;
		float _MassEarth;
		float _G;
		float _a;
		float _b;
		float _ge;
		float _gp;
		float _e2;
		float _m;
		float _f;
		float _k;

	public:
		Gravity();
		~Gravity();

		float g(float phi_geodetic, float altitude);
};


#endif
