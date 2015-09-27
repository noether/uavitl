/*
 *  XPlaneLat.cpp
 *  MisSockets
 *
 *  Created by Javier on 26/10/09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */

#include "XPlanePosition.h"
#include <vector>
#include <ostream>
#include "XplanePlane.h"



XPlanePosition::XPlanePosition():
	latitude(-999),
	longitude(-999),
	fmsl(-999),
	fagl(-999),
	altitudeIndic(-999),
	latSouth(-999),
	longWest(-999)
{
}


XPlanePosition::XPlanePosition(std::vector<char>::iterator & i) {   
	
	/*	
		i está apuntando al primer miembro correspondiente a los datos de indice 20:
	 */ 
	
	latitude= *reinterpret_cast<float*>(&*(i));
	longitude= *reinterpret_cast<float*>(&*(i+4));
	fmsl= *reinterpret_cast<float*>(&*(i+8)); 
	fagl= *reinterpret_cast<float*> (&*(i+12));
	// Desconocido= *reinterpret_cast<float*> (&*(i+16));
	altitudeIndic= *reinterpret_cast<float*> (&*(i+20));
	latSouth= *reinterpret_cast<float*> (&*(i+24));
	longWest= *reinterpret_cast<float*> (&*(i+28));

	// TODO: hay que ver que hay en el paquete, porque no cuadra
	
	i += 32;
}

XPlanePosition::~XPlanePosition() {
	
}


float XPlanePosition::getLatitude() {
	return latitude;
}


float XPlanePosition::getLongitude() {
	return longitude;
}


float XPlanePosition::getAltitudeFmsl() {
	return fmsl;
}


float XPlanePosition::getAltitudeFagl() {
	return fagl;
}

float XPlanePosition::getAltitudeIndic() {
	return altitudeIndic;
}

float XPlanePosition::getLatitudeS() {
	return latSouth;
}

float XPlanePosition::getLongitudeW() {
	return longWest;
}





std::ostream& XPlanePosition::oo (std::ostream& o)  const {
	return o	<< "Latitude: " << this->latitude << " degrees" << std::endl
				<< "Longitude: " << this->longitude << " degrees" << std::endl 
				<< "Altitude: " << this->fmsl << " fmsl" << std::endl
				<< "Altitude: " << this->fagl << " fagl" << std::endl
				<< "Altitude indicated: " << this->altitudeIndic << std::endl
				<< "Latitude South: " << this->latSouth << std::endl
				<< "Longitude West: " << this->longWest << std::endl;
}

void XPlanePosition::to_Dtg(std::vector<char> &dtg) const {
	
	
	
	// Vemos la longitud de nuestro dtg a enviar y aumentamos el tamaño para
	// introducir la nueva información:
	int long_dtg= dtg.size();
	
	dtg.resize(long_dtg+36);
	
	std::vector<char>::iterator i(dtg.begin()+long_dtg);
	
	int _index= 20;
	insert_in_dtg(i, _index);
	insert_in_dtg(i, latitude);
	insert_in_dtg(i, longitude);
	insert_in_dtg(i, fmsl);
	insert_in_dtg(i, fagl);
	insert_in_dtg(i, altitudeIndic);
	insert_in_dtg(i, latSouth);
	insert_in_dtg(i, longWest);
	
	
}

void XPlanePosition::accept(XPlanePlane *p) const {
	p->visit(*this);
}


