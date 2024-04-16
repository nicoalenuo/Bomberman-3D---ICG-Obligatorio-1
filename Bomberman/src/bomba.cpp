#include "../lib/bomba.h"
#include "lib/controlador.h"
#include "lib/global.h"

bomba::bomba(GLfloat x, GLfloat z, float tiempo, int largo) : objeto(x,z) {
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

personaje* bomba::getJugador() {
	return this->jugador;
}

void bomba::setJugador(personaje* jug) {
	this->jugador = jug;
}

void bomba::restarTiempo(int tiempo) {
    this->tiempoBomba -= tiempo;
    if (this->tiempoBomba <= 0) {
        this->tiempoBomba = 0;
    }
}

void bomba::actualizar() { // actualiza el tiempo, y si es cero, explota
    Controlador* controlador = Controlador::getInstance();
    objeto*** tablero = controlador->getTablero();
    bomberman* jugador = controlador->getBomberman();
    restarTiempo(global->frameDelay);
    if (this->tiempoBomba <= 0) {
        int largoTablero = controlador->getLargoTablero();
        int anchoTablero = controlador->getAnchoTablero();
        int x = (int)this->getCoordX();
        int z = (int)this->getCoordZ();
        bool alcanzaX = false;
        bool alcanzaZ = false;
        bool jugadorAlcanzado = false;

        for (int i = z+1; !alcanzaX && i < min(x + this->largoBomba+1, largoTablero);i++) { // x fijo, z incrementa
            if (tablero[x][i] != nullptr && tablero[x][i] != jugador) { // por ahora no toma en cuenta jugador
                alcanzaX = true;
                tablero[x][i]->actualizar();
            } else if (tablero[x][i] != nullptr) {
                jugadorAlcanzado = true;
            }
        }
        alcanzaX = false;
        for (int i = z - 1; !alcanzaX && i > max(x - this->largoBomba - 1, 0); i--) { // x fijo, z decrementa
            if (tablero[x][i] != nullptr && tablero[x][i] != jugador) { // por ahora no toma en cuenta jugador
                alcanzaX = true;
                tablero[x][i]->actualizar();
            } else if (tablero[x][i] != nullptr) {
                jugadorAlcanzado = true;
            }
        }

        for (int i = x + 1; !alcanzaX && i < min(z + this->largoBomba + 1, anchoTablero); i++) { // z fijo, x incrementa
            if (tablero[i][z] != nullptr && tablero[i][z] != jugador) { // por ahora no toma en cuenta jugador
                alcanzaZ = true;
                tablero[i][z]->actualizar();
            }
            else if (tablero[i][z] != nullptr) {
                jugadorAlcanzado = true;
            }
        }
        alcanzaZ = false;
        for (int i = x - 1; !alcanzaX && i > max(z - this->largoBomba - 1, 0); i--) { // z fijo, x decrementa
            if (tablero[i][z] != nullptr && tablero[i][z] != jugador) { // por ahora no toma en cuenta jugador
                alcanzaZ = true;
                tablero[i][z]->actualizar();
            }
            else if (tablero[i][z] != nullptr) {
                jugadorAlcanzado = true;
            }
        }

        // si el bomberman es alcanzado, debería de pasarle un bool de que murió en actualizar?
    } else {

    }
}

void bomba::dibujar() {

}