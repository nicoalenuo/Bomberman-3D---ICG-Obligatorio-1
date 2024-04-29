#pragma once

#ifndef BONIFICADOR_H
#define BONIFICADOR_H

#include <random>

#include "objeto.h"
#include "global.h"

enum tipo_poder { //agregar aca en caso de agregar mas bonificadores, y luego agregar casos al switch ControladorInterfaz
	AUMENTAR_ALCANCE_BOMBAS,
	INMORTALIDAD, // segundos de inmortalidad
	AUMENTAR_VELOCIDAD, //
	BOMBAS_ATRAVIESAN_ESTRUCTURAS,
	AUMENTAR_CANTIDAD_BOMBAS,
	BONIFICADOR_RANDOM, //NO ELIMINAR ESTE
};

class bonificador : public objeto {
private:
	tipo_poder tipo; 
	bool subiendo;
	float angulo;
public:
	bonificador(vector_3 pos, vector_3 tam, tipo_poder tipo);

	void eliminarBonificador(bool reducir);

	tipo_poder getTipo() const { return tipo; };
	void setTipo(tipo_poder tipo_p) { tipo = tipo_p; };

	void actualizar();
	void dibujar();
};


#endif

