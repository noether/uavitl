/*
 *  XPlaneJoystick.h
 *  MisSockets
 *
 *  Created by Javier on 06/11/09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */


#ifndef XPLANEJOYSTICK_H
#define XPLANEJOYSTICK_H

#include "XPlaneData.h"
#include <vector>
#include <iostream>
#include <string>


class XPlaneJoystick: public XPlaneData {
public:
	// =================
	// = Constructores =
	// =================
	XPlaneJoystick();
	XPlaneJoystick (float elev, float ail, float rudd /*,float  swRe, float vecRe*/);
	~XPlaneJoystick ();
	
	
	// ===========
	// = Métodos =
	// ===========
	float getElevator();	
	float getAileron();
	float getRudder();		
	//float getSweepRequest();
	//float getVectorRequest();

	
	virtual std::ostream& oo(std::ostream& o) const; // Redefinimos XPlaneData::oo
	virtual void to_Dtg(std::vector<char> &dtg) const;
	virtual void accept(XPlanePlane *p) const;
	
private:
	
	
	// =============
	// = Atributos =
	// =============
	
	float elevator;				// (0-1)
	float aileron;				// (0-1)
	float rudder;				// (0-1)
	//float sweepRequest;         // Degrees
	//float vectorRequest;		// Degrees
	
};





#endif // XPLANEJOYSTICK_H
