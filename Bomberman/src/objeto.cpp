#include "../lib/objeto.h"

float objeto::getCoordX() {
	return this->coord_x;
}

float objeto::getCoordZ() {
	return this->coord_z;
}

void objeto::setCoordX(float x) {
	this->coord_x = x;
}

void objeto::setCoordZ(float z) {
	this->coord_z = z;
}