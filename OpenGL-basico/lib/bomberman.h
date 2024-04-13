#pragma once

#ifndef BOMBERMAN_H
#define BOMBERMAN_H

#include "personaje.h"

class bomberman : public personaje {
private:
public:
	bomberman(int x, int z);
	void actualizar();
	void dibujar();
};


#endif

