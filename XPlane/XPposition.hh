/*
 *  XPlaneLat.h
 *  MisSockets
 *
 *  Created by Javier on 26/10/09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */


#ifndef XPLANEPOSITION_H
#define XPLANEPOSITION_H

#include "XPlaneData.h"
#include <vector>
#include <iostream>
#include <string>





class XPlanePosition: public XPlaneData {
public:
	// =================
	// = Constructores =
	// =================
	XPlanePosition();
	XPlanePosition (std::vector<char>::iterator &i) ;
	~XPlanePosition ();
	
	
	// ===========
	// = Métodos =
	// ===========
	float getLatitude();		// [degrees]
	float getLongitude();		// [degrees]
	float getAltitudeFmsl();	// [fmsl]	
	float getAltitudeFagl();	// [fagl]
	float getAltitudeIndic();	// [???]
	float getLatitudeS();
	float getLongitudeW();
	
	virtual std::ostream& oo(std::ostream& o) const; // Redefinimos XPlaneData::oo
	virtual void to_Dtg(std::vector<char> &dtg) const;
	virtual void accept(XPlanePlane *p) const;

	
private:
	
	
	// =============
	// = Atributos =
	// =============
	float latitude;
	float longitude;
	float fmsl;
	float fagl;
	float altitudeIndic;
	float latSouth;
	float longWest;
	
};





#endif // XPLANEPOSITION_H