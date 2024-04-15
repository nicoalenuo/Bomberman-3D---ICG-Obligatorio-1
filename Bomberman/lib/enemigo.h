#pragma once

#ifndef ENEMIGO_H
#define ENEMIGO_H

#include "personaje.h"


class enemigo : public personaje {
private:
	//en principio no tiene
public:
	enemigo(int x, int z);
	void actualizar();
	void dibujar();
};


#endif
