#pragma once

#ifndef DOOR_H
#define DOOR_H

#include "objeto.h"
#include "bomberman.h"

class door : public objeto {
private:
	bool visible;

public:
	door(vector_3 pos, vector_3 tam);

	bool getVisible();
	void setVisible(bool visible);

	bool intersecta(bomberman* b);

	void actualizar();
	void dibujar();
};

#endif

