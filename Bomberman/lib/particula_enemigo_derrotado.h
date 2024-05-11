#pragma once

#ifndef PARTICULA_ENEMIGO_DERROTADO_H
#define PARTICULA_ENEMIGO_DERROTADO_H

#include "particula.h"

class particula_enemigo_derrotado : public particula{
private:

public:
	particula_enemigo_derrotado(vector_3 pos, vector_3 tam, vector_3 ac, vector_3 vel);

	void actualizar();
	void dibujar();

};

#endif

