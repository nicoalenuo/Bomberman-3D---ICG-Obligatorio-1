#pragma once

#ifndef FUEGO_H
#define FUEGO_H

#include "objeto.h"

class fuego : public objeto{
private:

	int tiempoFuego;

public:
	fuego(posicion pos, tamanio tam, int tiempo);

	void actualizar();
	void dibujar();
};

#endif

