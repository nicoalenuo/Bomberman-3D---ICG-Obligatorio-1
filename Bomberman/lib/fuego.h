#pragma once

#ifndef FUEGO_H
#define FUEGO_H

#include "objeto.h"
#include "bomba.h"
#include "particula_fuego.h"

class fuego : public objeto{
private:
	int tiempoFuego;
	bool centro;
public:
	fuego(vector_3 pos, vector_3 tam, int tiempo, bool centro);

	void actualizar();
	void dibujar();
};

#endif

