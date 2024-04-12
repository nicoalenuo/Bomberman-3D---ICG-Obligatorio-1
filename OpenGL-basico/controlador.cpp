#include "controlador.h"
#include "global.h"
#include "bomba.h"
#include "estructura.h"
#include "objeto.h"
#include "enemigo.h"
#include "bomberman.h"

Controlador* Controlador::instancia = nullptr;

Controlador::Controlador() {
	//define atributos privados del controlador
	// me falta definir aun
	this->pausa = false;
	this->nivel = 1;
	for (int i = 0; i < this->largoTablero; ++i) {
		this->tablero[i] = new objeto* [anchoTablero];
		for (int j = 0; j < this->anchoTablero; j++) {
			this->tablero[i][j] = nullptr; // creo el tablero para instanciar lo grafico
		}
	}
	this->jugador = new bomberman(0,0);
}

bool Controlador::getPausa() {
	return this->getPausa();
}

void Controlador::setPausa(bool pau) {
	this->pausa = pau;
}

bool Controlador::getNivel() {
	return this->nivel;
}

void Controlador::setNivel(int niv) {
	this->nivel = niv;
}

void Controlador::pausar() {
	this->pausa = !(this->pausa);
}

void Controlador::aumentarNivel() {
	this->nivel++;
}

//crea la instancia de bomba, la asigna al arreglo de bombas en controlador, al del personaje que lo colocó y asigna el dueño a la bomba
void Controlador::crearBomba(int x, int z, personajes* pers) {
	bomba* bomb = new bomba(x,z,pers->getTiempoBomba(), pers->getLargoBomba());
	global::insertarBomba(this->bombas, bomb);
	bomb->setJugador(pers);
	global::insertarBomba(pers->getBomba(), bomb);
}

//ponerBomba lo que hace es obtener gracias a la matriz de objetos, si es valido poner una bomba en la posicion x, z. Y en caso de serlo crea la bomba
// si no, no hace nada
void Controlador::ponerBomba(int x, int z, personajes* pers){
	if (pers->bombaDisponible() &&  this->tablero[x][z] == nullptr) {
		crearBomba(x, z, pers);
	}
}