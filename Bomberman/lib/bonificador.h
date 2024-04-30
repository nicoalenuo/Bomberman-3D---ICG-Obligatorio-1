#pragma once

#ifndef BONIFICADOR_H
#define BONIFICADOR_H

#include <random>

#include "objeto.h"
#include "global.h"
#include "bomberman.h"
#include "particula_bonificador.h"

class bonificador : public objeto {
private:
	tipo_poder tipo; 
	bool subiendo, visible;
	int rotacion_y;
public:
	bonificador(vector_3 pos, vector_3 tam, tipo_poder tipo);

	tipo_poder getTipo() const { return tipo; };
	void setTipo(tipo_poder tipo_p) { tipo = tipo_p; };

	void actualizar();
	void dibujar();
};


#endif

