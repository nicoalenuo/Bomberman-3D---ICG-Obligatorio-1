#pragma once

#ifndef BOMBA_H
#define BOMBA_H

#include "objeto.h"

class bomba : public objeto {
private:
	float tiempoBomba;
	int largoBomba;
public:
	bomba(GLfloat x, GLfloat z, GLfloat anchoX, GLfloat anchoZ, GLfloat alt, float tiempo, int largo);
	float getTiempoBomba();
	void setTiempoBomba(float tiempo);
	int getLargoBomba();
	void setLargoBomba(int largo);
	void restarTiempo(int tiempo);
	void actualizar();
	void dibujar();
};

#endif

