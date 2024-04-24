#pragma once

#ifndef ESTRUCTURA_H
#define ESTRUCTURA_H

#include <random>

#include "objeto.h"
#include "particula.h"

class estructura : public objeto {
private:
	bool destructible; 
public:
	estructura(vector_3 pos, vector_3 tam, bool dest);
	~estructura();

	bool getDestructible() const { return destructible; };
	void setDestructible(bool dest) { destructible = dest; };

	void actualizar();
	void dibujar();
};


#endif

