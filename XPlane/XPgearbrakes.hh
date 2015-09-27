/*
 *  XPlaneGearBrakes.h
 *  MisSockets
 *
 *  Created by Javier on 11/11/09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef XPLANESGEARBRAKES_H
#define XPLANESGEARBRAKES_H

#include "XPlaneData.h"
#include <vector>
#include <iostream>
#include <string>


class XPlaneGearBrakes: public XPlaneData {
public:
	// =================
	// = Constructores =
	// =================
	XPlaneGearBrakes();
	XPlaneGearBrakes (float g, float wBrak, float leftBrak, float rightBrak) ;
	~XPlaneGearBrakes ();
	
	
	// ===========
	// = Métodos =
	// ===========
	float getGear();	
	float getWheelBrake();
	float getLeftBrake();		
	float getRightBrake();	

	virtual std::ostream& oo(std::ostream& o) const; // Redefinimos XPlaneData::oo
	virtual void to_Dtg(std::vector<char> &dtg) const;
	virtual void accept(XPlanePlane *p) const;
	
	
private:
	
	
	// =============
	// = Atributos =
	// =============
	
	// ??? es el gear integer?? 
	int gear;				  // 1= Down, 0= Up
	float wheelBrake;		  // 1= On
	float leftBrake;		  // (0-1)
	float rightBrake;         // (0-1)
	
};





#endif // XPLANESGEARBRAKES_H