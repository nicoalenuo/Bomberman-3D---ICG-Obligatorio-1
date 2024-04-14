#include "../lib/global.h"

global* global::instancia = nullptr;

global::global() {
    this->moverArriba = false;
    this->moverAbajo = false;
    this->moverDerecha = false;
    this->moverIzquierda = false;
    this->mouseX = 0;
}

global* global::getInstance() {
    if (instancia == nullptr) {
        instancia = new global();
    }
    return instancia;
}


bool global::getMoverArriba() {
    return this->moverArriba;
}

bool global::getMoverAbajo() {
    return this->moverAbajo;
}

bool global::getMoverDerecha() {
    return this->moverDerecha;
}

bool global::getMoverIzquierda() {
    return this->moverIzquierda;
}

void global::setMoverArriba(bool moverArriba) {
    this->moverArriba = moverArriba;
}

void global::setMoverDerecha(bool moverDerecha) {
    this->moverDerecha = moverDerecha;
}

void global::setMoverIzquierda(bool moverIzquierda) {
    this->moverIzquierda = moverIzquierda;
}

void global::setMoverAbajo(bool moverAbajo) {
    this->moverAbajo = moverAbajo;
}

int global::getMouseX() {
    return this->mouseX;
}

void global::setMouseX(int mouseX) {
    this->mouseX = mouseX;
}
