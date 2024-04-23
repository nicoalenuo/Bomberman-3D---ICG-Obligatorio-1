#pragma once

#ifndef ENEMIGO_H
#define ENEMIGO_H

#include "personaje.h"

class enemigo : public personaje {
private:

public:
	enemigo(vector_3 pos, vector_3 tam);

	void actualizar();
	void dibujar();
};


#endif
