#pragma once

#ifndef FUEGO_H
#define FUEGO_H

#include "objeto.h"
#include "bomba.h"
#include "particula_fuego.h"

class fuego : public objeto{
private:

	int tiempoFuego;

public:
	fuego(vector_3 pos, vector_3 tam, int tiempo);

	void actualizar();
	void dibujar();
};

#endif

