/*
 *  XPlaneData.cpp
 *  MisSockets
 *
 *  Created by Javier on 21/10/09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */

#include "XPlaneData.h"
#include "XPlaneTimes.h"
#include "XPlaneAttitude.h"
#include "XPlanePosition.h"



XPlaneData::XPlaneData(){

}

XPlaneData::~XPlaneData(){

}

std::ostream& operator<<(std::ostream &o, const XPlaneData &d) {
	return d.oo(o);
}






XPlaneData* XPlaneData::create(std::vector<char>::iterator &i) {
	
	/* 
		Crea un puntero a un objeto especificador del dato del datagrama.
		"implemented" es una variable temporal para indicar que no se conoce algún tipo
		enviado por X-Plane
	 */
				

		switch (*i) {
				
			case 1:
				// Hacemos que el iterador apunte directamente al principio de los datos
				i=i+4;
				
				
				return new XPlaneTimes(i);
				break;
				
			case 18:
				// Hacemos que el iterador apunte directamente al principio de los datos
				i=i+4;
				
				
				return new XPlaneAttitude(i);
				break;
				
			case 20:
				// Hacemos que el iterador apunte directamente al principio de los datos
				i=i+4;
				
				
				return new XPlanePosition(i);
				break;
				
				/* mas tipos de paquetes xPlane... */
				
			default:
				
				i=i+36;
				
				return 0;
				break;
		}
		
}




void XPlaneData::prologue_to_Dtg(std::vector<char> &dtg) {
	
	
	// Vemos la longitud de nuestro dtg a enviar y aumentamos el tamaño para
	// introducir la nueva información:
	int long_dtg= dtg.size();
	
	dtg.resize(long_dtg+5);
	
	std::vector<char>::iterator i(dtg.begin()+long_dtg);
	// std::vector<char>::iterator i_end(inf.end());
	
	// _separador= 34;
	insert_in_dtg(i, 'D');
	insert_in_dtg(i, 'A');
	insert_in_dtg(i, 'T');
	insert_in_dtg(i, 'A');
	insert_in_dtg(i, 0x34);
	
}


	












