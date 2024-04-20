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
	bonificador(posicion pos, tamanio tam);
	virtual string getNombre();
	virtual void setNombre(string nom);
	void actualizar();
	void dibujar();
};


#endif

