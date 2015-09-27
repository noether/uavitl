/*
 *  XPlaneThrottle.h
 *  MisSockets
 *
 *  Created by Javier on 12/11/09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */


#ifndef XPLANETHROTTLE_H
#define XPLANETHROTTLE_H

#include "XPlaneData.h"
#include <vector>
#include <iostream>
#include <string>


class XPlaneThrottle: public XPlaneData {
public:
	// =================
	// = Constructores =
	// =================
	XPlaneThrottle();
	XPlaneThrottle (float potencia);
	~XPlaneThrottle ();
	
	
	// ===========
	// = Métodos =
	// ===========
	float getThrottle1();	
		
	
	virtual std::ostream& oo(std::ostream& o) const; // Redefinimos XPlaneData::oo
	virtual void to_Dtg(std::vector<char> &dtg) const;
	virtual void accept(XPlanePlane *p) const;

	
private:
	
	
	// =============
	// = Atributos =
	// =============
	
	float powAvion1;				
};





#endif // XPLANEThrottle_H
