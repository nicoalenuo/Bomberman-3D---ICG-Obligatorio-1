#pragma once

#ifndef BONIFICADOR_H
#define BONIFICADOR_H

#include "objeto.h"
#include <string>

using namespace std;


class bonificador : public objeto {
private:
	string nombre; //tipo de poder
public:
	bonificador(GLfloat x, GLfloat z);
	virtual string getNombre();
	virtual void setNombre(string nom);
	void actualizar();
	void dibujar();
};


#endif

