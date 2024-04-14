#pragma once

#ifndef BOMBERMAN_H
#define BOMBERMAN_H

#include "personaje.h"

class bomberman : public personaje {
private:
	int vida;
	list<bomba*> bombas = list<bomba*>();
	int maxBomba;
	bool moverBomba;
	float tiempoBomba;
	int largoBomba;
	float velocidad;
public:
	bomberman(GLfloat x, GLfloat z);

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

	void actualizar();
	void dibujar();
};


#endif

