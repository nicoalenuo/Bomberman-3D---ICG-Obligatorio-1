#include "enemigo.h"

enemigo::enemigo(int x, int z) : personajes() {
	this->coord_x = (float) x;
	this->coord_z = (float) z;
	this->maxBomba = 0;
}