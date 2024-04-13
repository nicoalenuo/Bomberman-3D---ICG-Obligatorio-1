#pragma once

#ifndef PERSONAJE_H
#define PERSONAJE_H

#include <list>
#include "objeto.h"

using namespace std;

class bomba;

class personaje : public objeto { 
protected:
	int vida;
	list<bomba*> bombas = list<bomba*>(); 
	int maxBomba;
	bool moverBomba;
	float tiempoBomba;
	int largoBomba;
	float velocidad;
public:
	personaje();
	virtual int getVida();
	virtual void setVida(int vid);
	virtual list<bomba*> getBomba();
	virtual void setBomba(list<bomba*> bomb);
	virtual int getMaxBomba();
	virtual void setMaxBomba(int max);
	virtual bool getMoverBomba();
	virtual void setMoverBomba(bool mov);
	virtual float getTiempoBomba();
	virtual void setTiempoBomba(float tiempo);
	virtual int getLargoBomba();
	virtual void setLargoBomba(int largo);
	virtual float getVelocidad();
	virtual void setVelocidad(float vel);
	virtual bool bombaDisponible();
	virtual void ponerBomba(int x, int z);
	virtual void actualizar() = 0;
	virtual void dibujar() = 0;
};

#endif

