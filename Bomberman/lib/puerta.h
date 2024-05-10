#pragma once

#ifndef PUERTA_H
#define PUERTA_H

#include "objeto.h"
#include "bomberman.h"

class puerta : public objeto {
private:
	bool visible;

public:
	puerta(vector_3 pos, vector_3 tam);

	bool getVisible() const { return visible; };
	void setVisible(bool visible) { this->visible = visible; };

	bool intersecta(bomberman* b);

	void actualizar();
	void dibujar();
};

#endif

