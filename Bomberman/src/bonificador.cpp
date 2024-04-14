#include "../lib/bonificador.h"

bonificador::bonificador(GLfloat x, GLfloat z) : objeto(x,z) {
	this->nombre = "bonificador XD";
}

string bonificador::getNombre() {
	return this->nombre;
}

void bonificador::setNombre(string nom) {
	this->nombre = nom;
}

void bonificador::actualizar() {

}

void bonificador::dibujar() {

}