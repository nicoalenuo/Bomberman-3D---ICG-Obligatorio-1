#include "../lib/bomba.h"

bomba::bomba(int x, int z, float tiempo, int largo) : objeto() {
	this->coord_x = (float)x;
	this->coord_z = (float)z;
	this->tiempoBomba = tiempo;
	this->largoBomba = largo;
	this->jugador = nullptr;
}

float bomba::getTiempoBomba() {
	return this->tiempoBomba;
}

void bomba::setTiempoBomba(float tiempo) {
	this->tiempoBomba = tiempo;
}

int bomba::getLargoBomba() {
	return this->largoBomba;
}

void bomba::setLargoBomba(int largo) {
	this->largoBomba = largo;
}

personajes* bomba::getJugador() {
	return this->jugador;
}

void bomba::setJugador(personajes* jug) {
	this->jugador = jug;
}