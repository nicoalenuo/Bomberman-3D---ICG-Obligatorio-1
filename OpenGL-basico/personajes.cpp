#include "personajes.h"
#include "controlador.h"

personajes::personajes() : objeto() {
	this->vida = 1;
	this->moverBomba = false;
	this->largoBomba = 1;
	this->velocidad = 1; //Para poner algo pongo 1, falta probar y ajustar mediante la parte grafica
	this->tiempoBomba = 1; //Para poner algo pongo 1, falta probar y ajustar mediante la parte grafica
	this->maxBomba = 1;
}

int personajes::getVida() {
	return this->vida;
}

void personajes::setVida(int vid) {
	this->vida = vid;
}

list<bomba*> personajes::getBomba() {
	return this->bombas;
}

void personajes::setBomba(list<bomba*> bomb) {
	this->bombas = bomb;
}

int personajes::getMaxBomba() {
	return this->maxBomba;
}

void personajes::setMaxBomba(int max) {
	this->maxBomba = max;
}

bool personajes::getMoverBomba() {
	return this->moverBomba;
}

void personajes::setMoverBomba(bool mov) {
	this->moverBomba = mov;
}

float personajes::getTiempoBomba() {
	return this->tiempoBomba;
}

void personajes::setTiempoBomba(float tiempo) {
	this->tiempoBomba = tiempo;
}

int personajes::getLargoBomba() {
	return this->largoBomba;
}

void personajes::setLargoBomba(int largo) {
	this->largoBomba = largo;
}

float personajes::getVelocidad() {
	return this->velocidad;
}

void personajes::setVelocidad(float vel) {
	this->velocidad = vel;
}

bool personajes::bombaDisponible() {
	return (this->maxBomba>0 && (this->maxBomba == this->bombas.size()));
}

// el personaje manda una solicitud de que quiere poner una bomba, ya el controlador se encargará si puede o no
// las coordenadas las va a sacar la clase de la parte grafica mediante el controlador? o un controlador (nuevo) para grafico? (como? A)
void personajes::ponerBomba(int x, int z) {
	if (bombaDisponible()) {
		Controlador* controlador = Controlador::getInstance();
		controlador->ponerBomba(x,z,this);
	}
}