#pragma once

#ifndef BOMBA_H
#define BOMBA_H

#include <random>

#include "objeto.h"
#include "estructura.h"
#include "fuego.h"
#include "particula.h"

class bomba : public objeto {
private:
	int tiempoBomba, largoBomba;
public:
	bomba(posicion pos, tamanio tam, int tiempo, int largo);

	int getTiempoBomba();
	void setTiempoBomba(int tiempo);

	int getLargoBomba();
	void setLargoBomba(int largo);

	void actualizar();
	void dibujar();
};

#endif

