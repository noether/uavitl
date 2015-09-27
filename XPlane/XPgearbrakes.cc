/*
 *  XPlaneGearBrakes.cpp
 *  MisSockets
 *
 *  Created by Javier on 11/11/09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */

#include "XPlaneGearBrakes.h"

#include <vector>
#include <ostream>
#include "XPlanePlane.h"


XPlaneGearBrakes::XPlaneGearBrakes():
		gear(-999),	
		wheelBrake(-999),
		leftBrake(-999),
		rightBrake(-999)
{
}


XPlaneGearBrakes::XPlaneGearBrakes(float g, float wBrak, float leftBrak, float rightBrak) {   
	
	
	gear= g;				  // 1= Down, 0= Up
	wheelBrake= wBrak;		  // 1= On
	leftBrake= leftBrak;	  // (0-1)
	rightBrake= rightBrak;    // (0-1)
	
	
	
}

XPlaneGearBrakes::~XPlaneGearBrakes() {
	
}

float XPlaneGearBrakes::getGear() {
	return gear;
}

float XPlaneGearBrakes::getWheelBrake() {
	return wheelBrake;
}


float XPlaneGearBrakes::getLeftBrake() {
	return leftBrake;
}



float XPlaneGearBrakes::getRightBrake() {
	return rightBrake;
}



std::ostream& XPlaneGearBrakes::oo (std::ostream& o)  const {
	return o	<< "Gear: " << this->gear << std::endl
	<< "Wheelbrake: " << this->wheelBrake << std::endl 
	<< "Left Brake: " << this->leftBrake << std::endl
	<< "Right Brake: " << this->rightBrake << std::endl;
	
}


void XPlaneGearBrakes::to_Dtg(std::vector<char> &dtg) const {
	
	
	
	// Vemos la longitud de nuestro dtg a enviar y aumentamos el tamaño para
	// introducir la nueva información:
	int long_dtg= dtg.size();
	
	dtg.resize(long_dtg+36);
	
	std::vector<char>::iterator i(dtg.begin()+long_dtg);
	// std::vector<char>::iterator i_end(inf.end());
	
	int _index= 14;
	insert_in_dtg(i, _index);
	insert_in_dtg(i, gear);
	insert_in_dtg(i, wheelBrake);
	insert_in_dtg(i, leftBrake);
	insert_in_dtg(i, rightBrake);
	
	
}
void XPlaneGearBrakes::accept(XPlanePlane *p) const {
	p->visit(*this);
}
