/*
 *  XPlanePitch.h
 *  MisSockets
 *
 *  Created by Javier on 27/10/09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef XPLANEATTIUDE_H
#define XPLANEATTIUDE_H

#include "XPlaneData.h"
#include <vector>
#include <iostream>
#include <string>


class XPlaneAttitude: public XPlaneData {
public:
	// =================
	// = Constructores =
	// =================
	XPlaneAttitude();
	XPlaneAttitude (std::vector<char>::iterator &i) ;
	~XPlaneAttitude();
	
	
	// ===========
	// = Métodos =
	// ===========
	float getPitch();		
	float getRoll();	
	float getTrueHeading();
	float getMagneticHeading();
	float getMagVar();
	float getHeadingBug();
	
	float putPitch();		
	float putRoll();	
	float putTrueHeading();
	float putMagneticHeading();
	float putMagVar();
	float putHeadingBug();
	
	
	
	virtual std::ostream& oo(std::ostream& o) const; // Redefinimos XPlaneData::oo
	virtual void to_Dtg(std::vector<char> &dtg) const;
	virtual void accept(XPlanePlane *p) const;

private:
	
	
	// =============
	// = Atributos =
	// =============
	float pitch;
	float roll;
	float trueHeading;
	float magneticHeading;
	float magVar;
	float headingBug;
	
};

#endif
