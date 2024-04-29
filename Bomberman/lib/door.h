#pragma once

#ifndef DOOR_H
#define DOOR_H

#include "objeto.h"
#include "bomberman.h"

class door : public objeto {
private:
	bool abierta;
	bool visible;

public:
	door(vector_3 pos, vector_3 tam);

	bool getAbierta();
	void setAbierta(bool abierta);

	bool getVisible();
	void setVisible(bool visible);

	bool intersecta(bomberman* b);

	void actualizar();
	void dibujar();
};

#endif

