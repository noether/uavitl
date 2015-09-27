/*
 *  XPlaneThrottle.cpp
 *  MisSockets
 *
 *  Created by Javier on 12/11/09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */

#include "XPlaneThrottle.h"

#include <vector>
#include <ostream>
#include "XPlanePlane.h"

XPlaneThrottle::XPlaneThrottle():
		powAvion1(-999)
{
}


XPlaneThrottle::XPlaneThrottle(float potencia) {   
	
	
	powAvion1= potencia;
	
}

XPlaneThrottle::~XPlaneThrottle() {
	
}

float XPlaneThrottle::getThrottle1() {
	return powAvion1;
}




std::ostream& XPlaneThrottle::oo (std::ostream& o)  const {
	return o	<< "hp1: " << this->powAvion1 << std::endl;
	
	
}


void XPlaneThrottle::to_Dtg(std::vector<char> &dtg) const {
	
	
	
	// Vemos la longitud de nuestro dtg a enviar y aumentamos el tamaño para
	// introducir la nueva información:
	int long_dtg= dtg.size();
	
	dtg.resize(long_dtg+36);
	
	std::vector<char>::iterator i(dtg.begin()+long_dtg);
	// std::vector<char>::iterator i_end(inf.end());
	
	int _index=  25;
	insert_in_dtg(i, _index);
	insert_in_dtg(i, powAvion1);
		
}

void XPlaneThrottle::accept(XPlanePlane *p) const {
	p->visit(*this);
}


