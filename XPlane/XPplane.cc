/*
 *  XPlanePlane.cpp
 *  MisSockets
 *
 *  Created by Javier on 30/11/09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */

#include "XPlanePlane.h"



XPlanePlane::XPlanePlane(const XPlaneDataVector & v)
{

		for (XPlaneDataVector::const_iterator v_i(v.begin()), v_iii(v.end())
			 ; v_i != v_iii ; ++v_i)
			(*v_i)->accept(this);
}

XPlanePlane::~XPlanePlane()
{
}

void XPlanePlane::visit(const XPlaneTimes& t){
	tiempo=t;
}

void XPlanePlane::visit(const XPlanePosition& p){
	posicion=p;
}

void XPlanePlane::visit(const XPlaneAttitude& a){
	angulos=a;
}

void XPlanePlane::visit(const XPlaneJoystick& j){
	joystick=j;
}

void XPlanePlane::visit(const XPlaneGearBrakes& gb){
	frenos=gb;
}

void XPlanePlane::visit(const XPlaneThrottle& th){
	aceleracion=th;
}

void XPlanePlane::visit(const XPlaneGeneric& g){
	generico=g;
}

