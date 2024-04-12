#pragma once

#include <list>
#include "objeto.h"

using namespace std;

class bomba;

class personajes: public objeto { //abstracta
	protected:
		int vida;
		list<bomba*> bombas = list<bomba*>(); //se ordenan por tiempo de menor a mayor
		int maxBomba;
		bool moverBomba;
		float tiempoBomba;
		int largoBomba;
		float velocidad;
	public:
		personajes();
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
};

