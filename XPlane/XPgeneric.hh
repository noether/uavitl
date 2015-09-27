/*
 *  XPlaneGeneric.h
 *  MisSockets
 *
 *  Created by Javier on 16/11/09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */


#ifndef XPLANEGENERIC_H
#define XPLANEGENERIC_H

#include "XPlaneData.h"
#include <vector>
#include <iostream>
#include <string>


class XPlaneGeneric: public XPlaneData {
public:
	// =================
	// = Constructores =
	// =================
	XPlaneGeneric();
	XPlaneGeneric (float gen, int indx);
	~XPlaneGeneric ();
	
	
	// ===========
	// = Métodos =
	// ===========
	//float getGenericgen();	
	
	
	virtual std::ostream& oo(std::ostream& o) const; // Redefinimos XPlaneData::oo
	virtual void to_Dtg(std::vector<char> &dtg) const;
	virtual void accept(XPlanePlane *p) const;

	
private:
	
	
	// =============
	// = Atributos =
	// =============
	
	float generico;	
	int index;
};





#endif // XPlaneGeneric_H
