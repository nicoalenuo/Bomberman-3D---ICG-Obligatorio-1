#pragma once

#ifndef ENEMIGO_H
#define ENEMIGO_H

#include "personaje.h"

class enemigo : public personaje {
private:

public:
	enemigo(posicion pos, tamanio tam);

	void actualizar();
	void dibujar();
};


#endif
