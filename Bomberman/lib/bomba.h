#pragma once

#ifndef BOMBA_H
#define BOMBA_H

#include "objeto.h"
#include "estructura.h"
#include "fuego.h"

class bomba : public objeto {
private:
	int tiempoBomba;
	int largoBomba;
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

