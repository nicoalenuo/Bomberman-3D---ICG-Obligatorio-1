#pragma once

#ifndef PARTICULA_BONIFICADOR_H
#define PARTICULA_BONIFICADOR_H

#include "particula.h"

class particula_bonificador : public particula{
private:

public:
	particula_bonificador(vector_3 pos, vector_3 tam, vector_3 ac, vector_3 vel);

	void actualizar();
	void dibujar();
};

#endif

