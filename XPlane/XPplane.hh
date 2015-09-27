/*
 *  XPlanePlane.h
 *  MisSockets
 *
 *  Created by Javier on 30/11/09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef XPLANEPLANE_H
#define XPLANEPLANE_H

#include <vector>

#include "XPlaneData.h"

#include "XPlaneTimes.h"
#include "XPlanePosition.h"
#include "XPlaneAttitude.h"
#include "XPlaneJoystick.h"
#include "XPlaneGearBrakes.h"
#include "XPlaneThrottle.h"
#include "XPlaneGeneric.h"

class XPlanePlane  {
	
public:
	
	
	//XPlanePlane( );
	XPlanePlane(const XPlaneDataVector &v);
	~XPlanePlane();
	
	void visit(const XPlaneTimes& t);
	void visit(const XPlanePosition& p);
	void visit(const XPlaneAttitude& a);
	void visit(const XPlaneJoystick& j);
	void visit(const XPlaneGearBrakes& gb);
	void visit(const XPlaneThrottle& th);
	void visit(const XPlaneGeneric& g);
	
	// ============
	// = Attitude =
	// ================================================================
	float getPitch()			{return angulos.getPitch();}
	float getRoll()				{return angulos.getRoll();}
	float getTrueHeading()		{return angulos.getTrueHeading();}
	float getMagneticHeading()	{return angulos.getMagneticHeading();}
	float getMagVar()			{return angulos.getMagVar();}
	float getHeadingBug()		{return angulos.getHeadingBug();}
	//=================================================================
	
	
	
	// ============
	// = Position =
	// ================================================================
	float getLatitude()			{return posicion.getLatitude();}		
	float getLongitude()		{return posicion.getLongitude();}		
	float getAltitudeFmsl()		{return posicion.getAltitudeFmsl();}	
	float getAltitudeFagl()		{return posicion.getAltitudeFagl();}	
	float getAltitudeIndic()	{return posicion.getAltitudeIndic();}	
	float getLatitudeS()		{return posicion.getLatitudeS();}
	float getLongitudeW()		{return posicion.getLongitudeW();}
	//=================================================================

	
	
	// ============
	// = Times	  =
	// =================================================================
	float getElapsedTime()		{return tiempo.getElapsedTime();}	
	float getCockpitTimer()		{return tiempo.getCockpitTimer();}
	//float getLocalTime();											// Es la hora local en digital. No usado
	float getZuluTime()		{return tiempo.getZuluTime();}		// Mal obtenido del datagrama
	// =================================================================

	
	
private:
	
	XPlaneTimes tiempo;
	XPlanePosition posicion;
	XPlaneAttitude angulos; 
	XPlaneJoystick joystick; 
	XPlaneGearBrakes frenos;
	XPlaneThrottle aceleracion;
	XPlaneGeneric generico;
	
};


#endif // XPLANEPLANE_H