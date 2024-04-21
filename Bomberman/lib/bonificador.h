#pragma once

#ifndef BONIFICADOR_H
#define BONIFICADOR_H

#include "objeto.h"

enum tipo_poder { //Colocar aca los tipos

};

class bonificador : public objeto {
private:
	tipo_poder tipo; 
public:
	bonificador(posicion pos, tamanio tam, tipo_poder tipo);
	virtual tipo_poder getTipo();
	virtual void setTipo(tipo_poder tipo);
	void actualizar();
	void dibujar();
};


#endif

