#include "../lib/estructura.h"

estructura::estructura(GLfloat x, GLfloat z, bool dest) : objeto(x,z) {
	this->destructible = dest;
	this->powerUp = nullptr;

	global = global::getInstance();
}

bool estructura::getDestructible() {
	return this->destructible;
}

void estructura::setDestructible(bool dest) {
	this->destructible = dest;
}

bonificador* estructura::getPowerUp() {
	return this->powerUp;
}

void estructura::setPowerUp(bonificador* power) {
	this->powerUp = power;
}

void estructura::actualizar() {
	if (this->destructible) {
		//si es destructible entonces hace cosas en actualizar
	}
}

void estructura::dibujar() {
    
}
