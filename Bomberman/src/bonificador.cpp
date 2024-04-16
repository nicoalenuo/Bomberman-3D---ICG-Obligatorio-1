#include "../lib/bonificador.h"

bonificador::bonificador(GLfloat x, GLfloat z, GLfloat anchoX, GLfloat anchoZ, GLfloat alt) : objeto(x, z, anchoX, anchoZ, alt) {
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