/*
 *  XPlaneTimes.cpp
 *  MisSockets
 *
 *  Created by Javier on 21/10/09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */

#include "XPlaneTimes.h"
#include <vector>
#include <ostream>
#include "XPlanePlane.h"
XPlaneTimes::XPlaneTimes() :
	elapsedTime(-999),
	cockpitTime(-999),
	localTime1(-999),
	localTime2(-999),
	localTime3(-999),
	localTime4(-999),
	localTime5(-999)

{
}

XPlaneTimes::XPlaneTimes(std::vector<char>::iterator & i) {   
	
	/*	i está apuntando al primer miembro correspondiente a los datos de indice:
	
			(DATA)-> [44 41 54 41]   (Delimitador)-> 34  (Index)-> [1 0 0 0] (elsapsedTime)->[57 6b 7b 45] .. .. .. ..
			Entonces *i== 57;
	 
			A partir del (Index) todos los tipos mandan 32 bytes.
	 */ 
	elapsedTime= *reinterpret_cast<float*>(&*(i));
	cockpitTime= *reinterpret_cast<float*>(&*(i+4));
	localTime1= *reinterpret_cast<float*>(&*(i+8)); // (Formato desconocido) != float
	localTime2= *reinterpret_cast<float*> (&*(i+12));
	localTime3= *reinterpret_cast<float*> (&*(i+16));
	localTime4= *reinterpret_cast<float*> (&*(i+20));
	localTime5= *reinterpret_cast<float*> (&*(i+24));
	
	// TODO: Mirar exactamente donde se encuentra a hora Zulu
	zuluTime= *reinterpret_cast<float*>(&*(i+32));
	i += 32;
}

XPlaneTimes::~XPlaneTimes() {
	
}

float XPlaneTimes::getElapsedTime() {
	return elapsedTime;
}


float XPlaneTimes::getCockpitTimer() {
	return cockpitTime;
}


//float XPlaneTimes::getLocalTime(){
//	return localTime;
//}


float XPlaneTimes::getZuluTime() {
	return zuluTime;
}


std::ostream& XPlaneTimes::oo (std::ostream& o)  const {
	return o	<< "Elapsed Time: " << this->elapsedTime << "s" << std::endl
				<< "Cockpit Time: " << this->cockpitTime << "s" << std::endl 
				<< "Zulu Time: " << this->zuluTime << "h" << std::endl;
}
	
	
void XPlaneTimes::to_Dtg(std::vector<char> &dtg) const {
	


	// Vemos la longitud de nuestro dtg a enviar y aumentamos el tamaño para
	// introducir la nueva información:
	int long_dtg= dtg.size();

	dtg.resize(long_dtg+36);
	
	std::vector<char>::iterator i(dtg.begin()+long_dtg);
	// std::vector<char>::iterator i_end(inf.end());
	
	int _index= 1;
	insert_in_dtg(i, _index);
	insert_in_dtg(i, elapsedTime);
	insert_in_dtg(i, cockpitTime);
	insert_in_dtg(i, localTime1);
	insert_in_dtg(i, localTime2);
	insert_in_dtg(i, localTime3);
	insert_in_dtg(i, localTime4);
	insert_in_dtg(i, localTime5);
	insert_in_dtg(i, zuluTime);


}

void XPlaneTimes::accept(XPlanePlane *p) const {
	p->visit(*this);
}

