#include "../lib/objeto.h"

GLfloat objeto::getCoordX() {
	return this->coord_x;
}

GLfloat objeto::getCoordZ() {
	return this->coord_z;
}

void objeto::setCoordX(GLfloat x) {
	this->coord_x = x;
}

void objeto::setCoordZ(GLfloat z) {
	this->coord_z = z;
}