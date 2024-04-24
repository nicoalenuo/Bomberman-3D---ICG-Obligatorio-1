#pragma once

#ifndef BOMBA_H
#define BOMBA_H

#include "objeto.h"
#include "estructura.h"
#include "fuego.h"
#include "ControladorCamara.h"

class bomba : public objeto {
private:
	int tiempoBomba, largoBomba;
public:
	bomba(vector_3 pos, vector_3 tam, int tiempo, int largo);

	int getTiempoBomba() const { return tiempoBomba; };
	void setTiempoBomba(int tiempo) { tiempoBomba = tiempo; };

	int getLargoBomba() const { return largoBomba; };
	void setLargoBomba(int largo) {	largoBomba = largo; };

	void actualizar();
	void dibujar();
};

#endif

