#include "../lib/personaje.h"

personaje::personaje() : objeto() {
	this->vida = 1;
	this->moverBomba = false;
	this->largoBomba = 1;
	this->velocidad = (float) 0.1; //Para poner algo pongo 1, falta probar y ajustar mediante la parte grafica
	this->tiempoBomba = 1; //Para poner algo pongo 1, falta probar y ajustar mediante la parte grafica
	this->maxBomba = 1;
}

int personaje::getVida() {
	return this->vida;
}

void personaje::setVida(int vid) {
	this->vida = vid;
}

list<bomba*> personaje::getBomba() {
	return this->bombas;
}

void personaje::setBomba(list<bomba*> bomb) {
	this->bombas = bomb;
}

int personaje::getMaxBomba() {
	return this->maxBomba;
}

void personaje::setMaxBomba(int max) {
	this->maxBomba = max;
}

bool personaje::getMoverBomba() {
	return this->moverBomba;
}

void personaje::setMoverBomba(bool mov) {
	this->moverBomba = mov;
}

float personaje::getTiempoBomba() {
	return this->tiempoBomba;
}

void personaje::setTiempoBomba(float tiempo) {
	this->tiempoBomba = tiempo;
}

int personaje::getLargoBomba() {
	return this->largoBomba;
}

void personaje::setLargoBomba(int largo) {
	this->largoBomba = largo;
}

float personaje::getVelocidad() {
	return this->velocidad;
}

void personaje::setVelocidad(float vel) {
	this->velocidad = vel;
}

bool personaje::bombaDisponible() {
	return (this->maxBomba > 0 && (this->maxBomba == this->bombas.size()));
}