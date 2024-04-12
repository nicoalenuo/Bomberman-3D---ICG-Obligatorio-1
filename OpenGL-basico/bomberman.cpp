#include "bomberman.h"

bomberman::bomberman(int x, int z) : personajes() {
	this->coord_x = (float) x;
	this->coord_z = (float) z;
	this->maxBomba = 1;
}