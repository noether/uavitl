/*
 *  XPlaneData.h
 *  MisSockets
 *
 *  Created by Javier on 21/10/09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */

 // Clase base para los datos de un datagrama X-Plane:
#ifndef XPLANEDATA_H
#define XPLANEDATA_H

#include <tr1/memory>
#include <iostream>
#include <vector>

// Plantilla para copiar un tipo de variable en un buffer de caracteres:
template <typename T> void insert_in_dtg(std::vector<char>::iterator & i, T t) {
	std::memcpy(&*i, &t, sizeof(t));
	i += sizeof(t);
};

class XPlanePlane;

class XPlaneData {

public:
	
	
	XPlaneData();
	~XPlaneData();

	virtual std::ostream& oo(std::ostream &f) const=0; // Nos asegura el utilizar el "ostream" correcto según la clase derivada.
		
	friend std::ostream& operator<<(std::ostream &o, const XPlaneData &d);	
	
	
	static XPlaneData* create(std::vector<char>::iterator& i);
	
	// Crear la cabecera del datagrama a enviar:
	static void prologue_to_Dtg(std::vector<char> &dtg);

	virtual void to_Dtg(std::vector<char> &dtg) const=0;
	
	virtual void accept(XPlanePlane *p) const=0;



};

typedef std::vector<std::tr1::shared_ptr<XPlaneData> > XPlaneDataVector;

#endif // XPLANEDATA_H