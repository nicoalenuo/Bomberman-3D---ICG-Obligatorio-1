#pragma once

#ifndef ENEMIGO_H
#define ENEMIGO_H

#include "personaje.h"


class enemigo : public personaje {
private:

public:
	enemigo(GLfloat x, GLfloat z);
	void actualizar();
	void dibujar();
};


#endif
