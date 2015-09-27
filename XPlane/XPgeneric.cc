/*
 *  XPlaneGeneric.cpp
 *  MisSockets
 *
 *  Created by Javier on 16/11/09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */

#include "XPlaneGeneric.h"


#include <vector>
#include <ostream>
#include "XPlanePlane.h"

XPlaneGeneric::XPlaneGeneric():
		generico(-999),
		index(-999)
{
}
XPlaneGeneric::XPlaneGeneric(float gen, int indx) {   
	
	
	generico= gen;
	index=indx;
	
}

XPlaneGeneric::~XPlaneGeneric() {
	
}




std::ostream& XPlaneGeneric::oo (std::ostream& o)  const {
	return o	<< "gen: " << this->generico << std::endl;
	
	
}


void XPlaneGeneric::to_Dtg(std::vector<char> &dtg) const {
	
	
	
	// Vemos la longitud de nuestro dtg a enviar y aumentamos el tamaño para
	// introducir la nueva información:
	int long_dtg= dtg.size();
	
	dtg.resize(long_dtg+36);
	
	std::vector<char>::iterator i(dtg.begin()+long_dtg);
	// std::vector<char>::iterator i_end(inf.end());
	
	
	insert_in_dtg(i, this->index);
	insert_in_dtg(i, this->generico);
	
}

void XPlaneGeneric::accept(XPlanePlane *p) const {
	p->visit(*this);
}