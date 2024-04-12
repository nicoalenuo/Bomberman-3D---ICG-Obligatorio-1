#include "bonificador.h"

bonificador::bonificador(int x, int z) : objeto() {
	this->coord_x = (float) x;
	this->coord_z = (float) z;
	this->nombre = "bonificador XD";
}

string bonificador::getNombre() {
	return this->nombre;
}

void bonificador::setNombre(string nom) {
	this->nombre = nom;
}