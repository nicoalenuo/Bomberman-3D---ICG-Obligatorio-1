#include "../lib/bonificador.h"

bonificador::bonificador(posicion pos, tamanio tam) : objeto(pos, tam) {
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