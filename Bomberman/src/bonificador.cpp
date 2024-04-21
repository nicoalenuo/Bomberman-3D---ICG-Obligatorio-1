#include "../lib/bonificador.h"

bonificador::bonificador(posicion pos, tamanio tam, tipo_poder tipo) : objeto(pos, tam) {
	this->tipo = tipo;
}

void bonificador::actualizar() {

}

void bonificador::dibujar() {

}

tipo_poder bonificador::getTipo() {
	return tipo;
}

void bonificador::setTipo(tipo_poder tipo) {
	this->tipo = tipo;
}