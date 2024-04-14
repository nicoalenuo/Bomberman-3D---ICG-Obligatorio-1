#include "../lib/estructura.h"

estructura::estructura(GLfloat x, GLfloat z, bool dest) : objeto(x,z) {
	this->destructible = dest;
	this->powerUp = nullptr;
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

}

void estructura::dibujar() {

}
