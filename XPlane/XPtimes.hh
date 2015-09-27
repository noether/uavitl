/*
 *  XPlaneTimes.h
 *  MisSockets
 *
 *  Created by Javier on 21/10/09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */
#ifndef XPLANETIMES_H
#define XPLANETIMES_H

#include "XPlaneData.h"
#include <vector>
#include <iostream>
#include <string>


class XPlaneTimes: public XPlaneData {
public:
	// =================
	// = Constructores =
	// =================
	XPlaneTimes();
	XPlaneTimes (std::vector<char>::iterator &i) ;
	~XPlaneTimes ();
	
	
	// ===========
	// = Métodos =
	// ===========
	float getElapsedTime();	
	float getCockpitTimer();
	//float getLocalTime();		// Es la hora local en digital. No usado
	float getZuluTime();

	virtual std::ostream& oo(std::ostream& o) const; // Redefinimos XPlaneData::oo
	virtual void to_Dtg(std::vector<char> &dtg) const;
	virtual void accept(XPlanePlane *p) const;
	
private:
	
	
	// =============
	// = Atributos =
	// =============
	float elapsedTime;
	float cockpitTime;
	float localTime1;
	float localTime2;
	float localTime3;
	float localTime4;
	float localTime5;
	float zuluTime;
	
};





#endif // XPLANETIMES_H