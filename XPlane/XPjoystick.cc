/*
 *  XPlaneJoystick.cpp
 *  MisSockets
 *
 *  Created by Javier on 06/11/09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */

#include "XPlaneJoystick.h"
#include <vector>
#include <ostream>
#include "XPlanePlane.h"




XPlaneJoystick::XPlaneJoystick():
		elevator(-999),
		aileron(-999),
		rudder(-999)
{
}
XPlaneJoystick::XPlaneJoystick(float elev, float ail, float rudd /*, float  swRe, float vecRe*/) {   
	
	
	elevator= elev;			// (0-1)
	aileron= ail;			
	rudder=	rudd;			// (0-1)
	// sweepRequest= swRe;		// Degrees
	// vectorRequest= vecRe;	// Degrees
	


}

XPlaneJoystick::~XPlaneJoystick() {
	
}

float XPlaneJoystick::getElevator() {
	return elevator;
}

float XPlaneJoystick::getAileron() {
	return aileron;
}


float XPlaneJoystick::getRudder() {
	return rudder;
}



//float XPlaneJoystick::getSweepRequest() {
//	return sweepRequest;
//}

//float XPlaneJoystick::getVectorRequest() {
//	return vectorRequest;
//}


std::ostream& XPlaneJoystick::oo (std::ostream& o)  const {
	return o	<< "Jystick Elevator input: " << this->elevator << std::endl
	<< "Joystick Aileron Input: " << this->aileron << std::endl 
	<< "Joystick Rudder Input: " << this->rudder << std::endl;
	//<< "Joystick Sweep Request: " << this->sweepRequest << " degrees" << std::endl
	//<< "Joystick Vector Request: " << this->vectorRequest << " degrees" << std::endl;

}


void XPlaneJoystick::to_Dtg(std::vector<char> &dtg) const {
	
	
	
	// Vemos la longitud de nuestro dtg a enviar y aumentamos el tamaño para
	// introducir la nueva información:
	int long_dtg= dtg.size();
	
	dtg.resize(long_dtg+36);
	
	std::vector<char>::iterator i(dtg.begin()+long_dtg);
	// std::vector<char>::iterator i_end(inf.end());
	
	int _index= 8;
	insert_in_dtg(i, _index);
	insert_in_dtg(i, elevator);
	insert_in_dtg(i, aileron);
	insert_in_dtg(i, rudder);
	//insert_in_dtg(i, sweepRequest);
	//insert_in_dtg(i, vectorRequest);
	
	
}

void XPlaneJoystick::accept(XPlanePlane *p) const {
	p->visit(*this);
}
