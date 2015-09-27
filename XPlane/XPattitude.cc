/*
 *  XPlanePitch.cpp
 *  MisSockets
 *
 *  Created by Javier on 27/10/09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */

#include "XPlaneAttitude.h"
#include <vector>
#include <ostream>
#include "XPlanePlane.h"




XPlaneAttitude::XPlaneAttitude():
	pitch(-999),
	roll(-999),
	trueHeading(-999),
	magneticHeading(-999),
	magVar(-999),
	headingBug(-999)
{
}



XPlaneAttitude::XPlaneAttitude(std::vector<char>::iterator & i) {   
	
	/*	
	 i está apuntando al primer miembro correspondiente a los datos de indice 20:
	 */ 
	
	pitch= *reinterpret_cast<float*>(&*(i));
	roll= *reinterpret_cast<float*>(&*(i+4));
	trueHeading= *reinterpret_cast<float*>(&*(i+8)); 
	magneticHeading= *reinterpret_cast<float*> (&*(i+12));
	magVar= *reinterpret_cast<float*> (&*(i+16));
	headingBug= *reinterpret_cast<float*> (&*(i+20));
	//desconocido= *reinterpret_cast<float*> (&*(i+24));
	//desconocido= *reinterpret_cast<float*> (&*(i+28));
		
	i += 32;
}






XPlaneAttitude::~XPlaneAttitude() {
	
}


float XPlaneAttitude::getPitch() {
	return pitch;
}


float XPlaneAttitude::getRoll() {
	return roll;
}


float XPlaneAttitude::getTrueHeading() {
	return trueHeading;
}


float XPlaneAttitude::getMagneticHeading() {
	return magneticHeading;
}

float XPlaneAttitude::getMagVar() {
	return magVar;
}

float XPlaneAttitude::getHeadingBug() {
	return headingBug;
}

std::ostream& XPlaneAttitude::oo (std::ostream& o)  const {
	return o	<< "Pitch: " << this->pitch << " degrees" << std::endl
	<< "Roll: " << this->roll << " degrees" << std::endl 
	<< "True Heading: " << this->trueHeading << " degrees" << std::endl
	<< "Magnetic Heading: " << this->magneticHeading << " degrees" << std::endl
	<< "Mag Var: " << this->magVar << " degrees" << std::endl
	<< "Heading bug: " << this->headingBug << " degrees" << std::endl;
}

void XPlaneAttitude::to_Dtg(std::vector<char> &dtg) const {
	
	
	
	// Vemos la longitud de nuestro dtg a enviar y aumentamos el tamaño para
	// introducir la nueva información:
	int long_dtg= dtg.size();
	
	dtg.resize(long_dtg+36);
	
	std::vector<char>::iterator i(dtg.begin()+long_dtg);
	// std::vector<char>::iterator i_end(inf.end());
	
	int _index= 18;
	insert_in_dtg(i, _index);
	insert_in_dtg(i, pitch);
	insert_in_dtg(i, roll);
	insert_in_dtg(i, trueHeading);
	insert_in_dtg(i, magneticHeading);
	insert_in_dtg(i, magVar);
	insert_in_dtg(i, headingBug);
	
	
}
void XPlaneAttitude::accept(XPlanePlane *p) const {
	p->visit(*this);
}



